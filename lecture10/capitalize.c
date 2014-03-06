#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void capitalize(char* str) {
    while (*str != '\0') {
        *str &= 0x3F;
        str++;     
    } 
}

int main() {
    char* test;
    *test = "lowercase";
    printf("%s", test);
    capitalize(test);
    printf("%s", test);
}