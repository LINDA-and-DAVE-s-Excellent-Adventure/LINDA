#include "encoding.h"
#include <stdio.h>

void encode_hamming7_4(const char *text, int data_length, uint8_t *codeword) {
    int i, j = 0;
    printf("Beginning to encode %s\n", text);

    for(i=0; i<data_length; ++i) {
        // Process each character in the text as a byte
        uint8_t byte = text[i];

        // Conver the character byte into binary data bits
        for(int bit=7; bit>-1; --bit) {
            uint8_t data_bit = (byte >> bit) & 0x01;
            printf("Processing byte: %u -- bit %d: %u\n", byte, bit, data_bit);

            // Calculate parity bits (assuming positions 1, 2, 4 are parity)
            int p1 = (data_bit & 0x01) + ((byte >> 2) & 0x01)  + ((byte >> 4) & 0x01);
            int p2 = ((byte >> 1) & 0x01) + ((byte >> 4) & 0x01) + ((byte >> 6) & 0x01);
            int p3 = data_bit + ((byte >> 1) & 0x01) + ((byte >> 3) & 0x01); 

            // Place parity bits and the processed data bit
            codeword[j++] = (p1 % 2) + '0';  
            codeword[j++] = (p2 % 2) + '0'; 
            codeword[j++] = data_bit + '0'; // Insert data bit directly
            codeword[j++] = (p3 % 2) + '0';
        }
        printf("**** Done with %s\n", text[i]);
    }
    return;
}

void decode_hamming7_4(const uint8_t *codeword, int codeword_length, uint8_t *data) {
    int i, j = 0;

    // Correction lookup table
    const int correction_table[8] = {
        0, // No error
        3,  
        5, 
        6,
        1,
        2,
        4,
        7 
    };

    // Process groups of 7 bit codewords
    for(i=0; i<codeword_length; ++i) {
        // Recalculate parity bits 
        int p1 = (codeword[i*7] + codeword[i*7 + 2] + codeword[i*7 + 4] + codeword[i*7 + 6]) % 2;
        int p2 = (codeword[i*7] + codeword[i*7 + 1] + codeword[i*7 + 4] + codeword[i*7 + 5]) % 2;
        int p3 = (codeword[i*7 + 1] + codeword[i*7 + 2] + codeword[i*7 + 3] + codeword[i*7 + 4]) % 2;

        // Error syndrome -- tells whether there is an error present or not
        int error_syndrome = p3 * 4 + p2 * 2 + p1;

        // Correction
        if(error_syndrome != 0) {
            // Adjust by -1 to account for 
            int bit_postition = correction_table[error_syndrome] - 1; 
        }

        // Extract data bits (D3, D5, D6, D7) and put into 'data' 
        data[j++] = (codeword[i*7 + 2] << 3) | (codeword[i*7 + 4] << 2) |
                    (codeword[i*7 + 5] << 1) | (codeword[i*7 + 6]);
    }
}