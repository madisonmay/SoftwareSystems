/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Returns a heap-allocated string with length n, with
// the given string in the middle, surrounded by fillchar.
//
// For example, if s is allen, n is 10 and fillchar is .
// the result is ..allen... 

char *center(char *s, int n, char fillchar)
{
    // calculate string length and offset
    int length =  strlen(s);
    int start = n/2 - length/2;

    // allocate space for string
    char *centered = malloc(sizeof(char)*(n+1));
    int i = 0;

    // fill first half with padding
    while (i < start) {
        centered[i] = fillchar;
        i++;
    }

    // copy string to proper location
    strcpy(&centered[i], s);
    i += length;

    // fill second half with padding
    while (i < n) {
        centered[i] = fillchar;
        i++;
    }

    centered[n] = '\0';
    return centered;
}


int main (int argc, char *argv[])
{
    char *s = center("Software", 30, '.');
    printf("%s\n", s);

    char *s2 = center("Systems", 31, '-');
    printf("%s\n", s2);

    char *s3 = center("Spring 2014", 32, '*');
    printf("%s\n", s3);

    char *s4 = center("Exam 1", 33, '^');
    printf("%s\n", s4);

    return 0;
}
