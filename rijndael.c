/*
 * TODO: Add your name and student number here, along with
 *       a brief description of this code.
 */

#include <stdlib.h>
// TODO: Any other files you need to include should go here

#include "rijndael.h"

/*
 * Operations used when encrypting a block
 */
void sub_bytes(unsigned char *block) {
  // TODO: Implement me!
}

void shift_rows(unsigned char *block) {
  // TODO: Implement me!
  unsigned char temp;

    // Row 1 (indices: 1,5,9,13) — shift left by 1
    temp = block[1];
    block[1]  = block[5];
    block[5]  = block[9];
    block[9]  = block[13];
    block[13] = temp;

    // Row 2 (indices: 2,6,10,14) — shift left by 2
    temp = block[2];
    block[2]  = block[10];
    block[10] = temp;
    temp = block[6];
    block[6]  = block[14];
    block[14] = temp;

    // Row 3 (indices: 3,7,11,15) — shift left by 3
    temp = block[15];
    block[15] = block[11];
    block[11] = block[7];
    block[7]  = block[3];
    block[3]  = temp;

}

void mix_columns(unsigned char *block) {
  // TODO: Implement me!
}

/*
 * Operations used when decrypting a block
 */
void invert_sub_bytes(unsigned char *block) {
  // TODO: Implement me!
}

void invert_shift_rows(unsigned char *block) {
  // TODO: Implement me!
}

void invert_mix_columns(unsigned char *block) {
  // TODO: Implement me!
}

/*
 * This operation is shared between encryption and decryption
 */
void add_round_key(unsigned char *block, unsigned char *round_key) {
  // TODO: Implement me!
  for (int i = 0; i < BLOCK_SIZE; i++) {
    block[i] ^= round_key[i];
  }
}

/*
 * This function should expand the round key. Given an input,
 * which is a single 128-bit key, it should return a 176-byte
 * vector, containing the 11 round keys one after the other
 */
unsigned char *expand_key(unsigned char *cipher_key) {
  // TODO: Implement me!
  return 0;
}

/*
 * The implementations of the functions declared in the
 * header file should go here
 */
unsigned char *aes_encrypt_block(unsigned char *plaintext, unsigned char *key) {
  // TODO: Implement me!
  unsigned char *output =
      (unsigned char *)malloc(sizeof(unsigned char) * BLOCK_SIZE);
  return output;
}

unsigned char *aes_decrypt_block(unsigned char *ciphertext,
                                 unsigned char *key) {
  // TODO: Implement me!
  unsigned char *output =
      (unsigned char *)malloc(sizeof(unsigned char) * BLOCK_SIZE);
  return output;
}
