#include <stdio.h>
#include <stdlib.h>
#include "rijndael.h"

void print_128bit_block(unsigned char *block, const char *label) {
    printf("\n%s\n", label);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%3d ", block[i * 4 + j]);
        }
        printf("\n");
    }
}

void print_hex_block(unsigned char *block) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x ", block[i]);
    }
    printf("\n");
}

int main() {
    unsigned char plaintext[BLOCK_SIZE] = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16
    };

    unsigned char key[BLOCK_SIZE] = {
        50, 20, 46, 86,
        67, 9, 70, 27,
        75, 17, 51, 17,
        4, 8, 6, 99
    };

    unsigned char *ciphertext = aes_encrypt_block(plaintext, key);
    unsigned char *recovered = aes_decrypt_block(ciphertext, key);

    print_128bit_block(plaintext, "\033[1;32mOriginal Plaintext:\033[0m");
    printf("\nHex view: "); print_hex_block(plaintext);

    print_128bit_block(ciphertext, "\033[1;34mCiphertext (Encrypted):\033[0m");
    printf("\nHex view: "); print_hex_block(ciphertext);

    print_128bit_block(recovered, "\033[1;33mRecovered Plaintext:\033[0m");
    printf("\nHex view: "); print_hex_block(recovered);

    free(ciphertext);
    free(recovered);
    return 0;
}
