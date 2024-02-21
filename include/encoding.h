#ifndef ENCODING_H
#define ENCODING_H

#include <stdint.h>

// Hamming (7,4)
#define DATA_BITS 4
#define CODEWORD_BITS 7

// Hamming encoding/decoding functions
void encode_hamming7_4(const uint8_t *data, int data_length, uint8_t *codeword);
void decode_hamming7_4(const uint8_t *codeword, int codeword_length, uint8_t *data);

#endif