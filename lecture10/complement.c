#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int complement(int bin) {
    return (bin ^ 0xffffffff) + 1;
}

uint8_t low_bits(uint8_t byte, int bits) {
    return byte & ((1 << bits) - 1);
}

int main() {
    uint8_t bin = 0xff;
    int n = 5;
    printf("%i\n", low_bits(bin, n));
}