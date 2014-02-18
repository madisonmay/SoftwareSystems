/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *tracks[] = {
    "So What",
    "Freddie Freeloader",
    "Blue in Green",
    "All Blues",
    "Flamenco Sketches"
};

/* Returns a heap-allocated string that contains the strings 
   from the given array, joined up with no spaces between.
*/
char *strjoin(char *array[], int n)
{
    int i, j, length;

    /* calculate size of dynamically allocated string*/
    for (i=0; i<n; i++) {
        length += strlen(array[i]);
    } 

    /* init empty string of proper size*/
    char *joined = malloc(sizeof(char)*(length+1));

    /* concat strings */
    for (j=0; j<n; j++) {
        strcat(joined, array[j]);
    } 

    return joined;
}


int main (int argc, char *argv[])
{
    char *s = strjoin(tracks, 5);
    printf("%s\n", s);
    return 0;
}
