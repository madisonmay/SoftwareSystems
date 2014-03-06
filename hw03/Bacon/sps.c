//gcc sps.c -o sps -I hiredis -L hiredis -lhiredis -lm
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hiredis/hiredis.h>

/*
Given an actor/actress name, finds the list of all movies the actor/actor has acted in
Then, for each movie a full cast list is found and added to a temporary redis set.
Finally, the set is converted to an array and returned.
*/
redisReply* successors(char* person, redisContext* c) {
    redisReply* movies;
    redisReply* people;
    redisReply* nodes;

    // get list of movies person has acted in
    movies = redisCommand(c, "SMEMBERS %s", person);
    int i;
    int j;
    for (i = 0; i < movies->elements; i++) {

        // find all people who acted in the given movie
        people = redisCommand(c, "SMEMBERS %s", movies->element[i]->str);
        for (j = 0; j < people->elements; j++) {
            // add each to a temporary redis set obj
            redisCommand(c, "SADD SUCCESSORS %s", people->element[j]->str);
        }
        freeReplyObject(people);
    }
    freeReplyObject(movies);

    nodes = redisCommand(c, "SMEMBERS SUCCESSORS");

    // remove temporary set from redis
    redisCommand(c, "DEL SUCCESSORS");
    return nodes;
}

/*
Takes a start character as input, initializes a redis connection, and 
outsources work to the successors function.

start: actor/actress name
successors: function that returns all actors/actresses who have acted with the start actor/actress
*/
char** request(char* start, redisReply* (*successors)(char*, redisContext*)) {
    redisContext *c;
    redisReply *movies;
    redisReply *people;

    // establish redis connection
    struct timeval timeout = { 1, 500000 }; // 1.5 seconds
    c = redisConnectWithTimeout("127.0.0.1", 6379, timeout);
    if (c == NULL || c->err) {
        if (c) {
            printf("Connection error: %s\n", c->errstr);
            redisFree(c);
        } else {
            printf("Connection error: can't allocate redis context\n");
        }
        exit(1);
    }

    redisReply* new_states = successors(start, c);
    int i;

    // iterate over results and output actor/actress names
    for (i = 0; i < new_states->elements; i++) {
        printf("%i) %s\n", i, new_states->element[i]->str);
    }
    return 0;
}

int main() {
    char* start = (char *) "Watson, Emma (II)";
    request(start, &successors);
    return 0;
}
