/* YExample code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define NUM_TRACKS 5

char tracks[][80] = {
    "So What",
    "Freddie Freeloader",
    "Blue in Green",
    "All Blues",
    "Flamenco Sketches"
};


// Finds all tracks that contain the given string.
//
// Prints track number and title.
void find_track(char search_for[])
{
    int i;
    for (i=0; i<NUM_TRACKS; i++) {
    	if (strstr(tracks[i], search_for)) {
    	    printf("Track %i: '%s'\n", i, tracks[i]);
    	}
    }
}

// Finds all tracks that match the given pattern.
//
// Prints track number and title if match found
// Skips over track names that do not match
void find_track_regex(char pattern[])
{
    regex_t re;
    int err;
    int i;
    char msg[100];

    // compilation
    err = regcomp(&re, pattern, 0);
    if (err) {
        fprintf(stderr, "Regex compilation failed with error code: %i\n", err);
        exit(1);
    }

    // iterate over tracks
    for (i=0; i<NUM_TRACKS; i++) {
        // regex execution
        err = regexec(&re, tracks[i], 0, NULL, 0);
        if (err == REG_NOMATCH) {
            // no-op
        } else if (err) {
            regerror(err, &re, msg, sizeof(msg));
            fprintf(stderr, "Regex execution failed: %s\n", msg);
            exit(1);
        } else {
            printf("Track %i: '%s'\n", i, tracks[i]);
        }
    }

    // cleanup
    regfree(&re);
}

// Truncates the string at the first newline, if there is one.
void rstrip(char s[])
{
    char *ptr = strchr(s, '\n');
    if (ptr) {
	*ptr = '\0';
    }
}

int main (int argc, char *argv[])
{
    char search_for[80];

    /* take input from the user and search */
    printf("Search for: ");
    fgets(search_for, 80, stdin);
    rstrip(search_for);

    // find_track(search_for);
    find_track_regex(search_for);

    return 0;
}
