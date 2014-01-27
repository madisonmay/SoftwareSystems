/* 
    A simple program for card counting

    parse_card: user input converted to int that represents card value
    count_delta: calculates how global count should be modified
    count_cards: wrapper function that handles initialization, delegation

    Copyright 2014, Madison May
*/

#include <stdio.h>
#include <stdlib.h>

/* Converts an array of characters (card_name) into a corresponding 
   numeric value based on the value of the card.  Input limited to 
   two characters.
*/
int parse_card(const char card_name[3]) {
    int val = 0;
    switch(card_name[0]) {
        case 'K':
        case 'Q':
        case 'J':
            val = 10;
            break;
        case 'A': 
            val = 11;
            break;
        case 'X':
            break;
        default:
            if ((val > 0) || (val < 11)) {
                val = atoi(card_name);
            }
    }
    return val;
}

/* Calculates how the global count should be changed */
int count_delta(int val) {
    if ((val > 2) && (val < 7)) {
        return 1;
    } else if (val == 10) {
        return -1;
    }
    return 0;
}

/* A card counter function that wraps parse_card and count_delta.
   Handles initialization, then queries the user for input cards
   and delegates to parse_card and count_delta for the "heavy lifting"
*/
void count_cards() {
    char card_name[3];
    int count = 0;
    while (card_name[0] != 'X') {
        puts("Enter the card name: ");
        scanf("%2s", card_name);

        int val = parse_card(card_name);
        if (!val) {
            puts("Card not recognized.");
            continue;
        }
        count += count_delta(val);
        printf("Current count: %i\n", count);
    }
}

int main() {
    count_cards();
    return 0;
}