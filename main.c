#include <stdio.h>
#include <stdlib.h>

#include "rijndael.h"

void print_128bit_block(unsigned char *block) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      unsigned char value = BLOCK_ACCESS(block, i, j);

      // Print spaces before small numbers to ensure that everything is aligned
      // and looks nice
      if (value < 10) printf(" ");

      if (value < 100) printf(" ");

      printf("%d", value);
    }
    printf("\n");
  }
}

void print_block(unsigned char *block) {
  for (int i = 0; i < BLOCK_SIZE; i++) {
      printf("%02x ", block[i]);
  }
  printf("\n");
}



int main() {
  // test case for all_round_key
  unsigned char block[BLOCK_SIZE]     = {0x00, 0x01, 0x02, 0x03,
    0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b,
    0x0c, 0x0d, 0x0e, 0x0f};

  unsigned char round_key[BLOCK_SIZE] = {0x0f, 0x0e, 0x0d, 0x0c,
    0x0b, 0x0a, 0x09, 0x08,
    0x07, 0x06, 0x05, 0x04,
    0x03, 0x02, 0x01, 0x00};

  printf("Before add_round_key:\n");
  print_block(block);

  add_round_key(block, round_key);

  printf("After add_round_key:\n");
  print_block(block);

    // Shift Rows Test
    unsigned char shift_test[16] = {
      0x00, 0x01, 0x02, 0x03,
      0x10, 0x11, 0x12, 0x13,
      0x20, 0x21, 0x22, 0x23,
      0x30, 0x31, 0x32, 0x33
  };

  printf("\nBefore shift_rows:\n");
  print_block(shift_test);

  shift_rows(shift_test);

  printf("After shift_rows:\n");
  print_block(shift_test);

  // sub_byte test case
  unsigned char sub_test[BLOCK_SIZE] = {
    0x00, 0x11, 0x22, 0x33,
    0x44, 0x55, 0x66, 0x77,
    0x88, 0x99, 0xaa, 0xbb,
    0xcc, 0xdd, 0xee, 0xff
  };
  
  printf("\nBefore sub_bytes:\n");
  print_block(sub_test);
  
  sub_bytes(sub_test);
  
  printf("After sub_bytes:\n");
  print_block(sub_test);

  // test case for mix_test
  unsigned char mix_test[16] = {
    0xdb, 0x13, 0x53, 0x45,
    0xf2, 0x0a, 0x22, 0x5c,
    0x01, 0x01, 0x01, 0x01,
    0xc6, 0xc6, 0xc6, 0xc6
  };

  printf("\nBefore mix_columns:\n");
  print_block(mix_test);

  mix_columns(mix_test);

  printf("After mix_columns:\n");
  print_block(mix_test);


  // test case for expand_key
  unsigned char test_key[16] = {
    0x2b, 0x7e, 0x15, 0x16,
    0x28, 0xae, 0xd2, 0xa6,
    0xab, 0xf7, 0x15, 0x88,
    0x09, 0xcf, 0x4f, 0x3c
  };

  unsigned char *round_keys = expand_key(test_key);

  printf("\nExpanded Keys:\n");
  for (int i = 0; i < 176; i++) {
      printf("%02x ", round_keys[i]);
      if ((i + 1) % 16 == 0) printf("\n");
  }

  free(round_keys);


  unsigned char plaintext[16] = {1, 2,  3,  4,  5,  6,  7,  8,
                                 9, 10, 11, 12, 13, 14, 15, 16};
  unsigned char key[16] = {50, 20, 46, 86, 67, 9, 70, 27,
                           75, 17, 51, 17, 4,  8, 6,  99};

  unsigned char *ciphertext = aes_encrypt_block(plaintext, key);
  unsigned char *recovered_plaintext = aes_decrypt_block(ciphertext, key);

  printf("############ ORIGINAL PLAINTEXT ###########\n");
  print_128bit_block(plaintext);

  printf("\n\n################ CIPHERTEXT ###############\n");
  print_128bit_block(ciphertext);

  printf("\n\n########### RECOVERED PLAINTEXT ###########\n");
  print_128bit_block(recovered_plaintext);

  free(ciphertext);
  free(recovered_plaintext);

  return 0;
}
