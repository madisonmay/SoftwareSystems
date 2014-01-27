/* Prompts the user for input and puts the reply in the given buffer.

   User input is truncated to the first two characters.

   prompt: string prompt to display
   card_name: buffer where result is stored
*/

#include <stdio.h>
#include <stdlib.h>

int parse_card(const char card[3]) {
    int val = 0;
    switch(card[0]) {
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
                val = atoi(card);
            }
    }
    return val;
}

int count_delta(int val) {
    if ((val > 2) && (val < 7)) {
        return 1;
    } else if (val == 10) {
        return -1;
    }
    return 0;
}

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