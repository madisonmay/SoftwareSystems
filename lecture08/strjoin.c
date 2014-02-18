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
   from the given array, joined up with no spaces between. */
char *strjoin(char *array[], int n)
{
    int i, j;
    int cumulative[n+1];
    cumulative[0] = 0;

    /* calculate size of dynamically allocated string
       and store list of cumulative sizes for strncpy */
    for (i=0; i<n; i++) {
        cumulative[i+1] = cumulative[i] + strlen(array[i]);;
    } 

    /* init empty string of proper size */
    char *joined = (char *) malloc(sizeof(char)*(cumulative[n]));
    joined[0] = '\0';

    /* copy strings into the proper blocks of memory */
    for (j=0; j<n; j++) {
        int index = cumulative[j];
        strcpy(&joined[index], array[j]);
    } 

    return joined;
}


int main (int argc, char *argv[])
{
    char *s = strjoin(tracks, 5);
    printf("%s\n", s);
    return 0;
}
