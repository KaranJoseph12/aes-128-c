// main.c

#include <stdio.h>
#include <stdlib.h>
#include "rijndael.h"

void print_128bit_block(unsigned char *block) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%3d ", block[i * 4 + j]);
        }
        printf("\n");
    }
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
    unsigned char *recovered_plaintext = aes_decrypt_block(ciphertext, key);

    printf("\nOriginal Plaintext:\n");
    print_128bit_block(plaintext);

    printf("\nCiphertext (Encrypted):\n");
    print_128bit_block(ciphertext);

    printf("\nRecovered Plaintext:\n");
    print_128bit_block(recovered_plaintext);

    free(ciphertext);
    free(recovered_plaintext);

    return 0;
}
