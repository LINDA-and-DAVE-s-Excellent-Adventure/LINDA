#include "encoding.h"

void encode_hamming(const uint8_t *data, int data_length, uint8_t *codeword) {
    int i, j = 0;

    for(i=0; i<data_length; ++i) {
        // Extract 4 data bits
        uint8_t data_bits = (data[i] >> 4) & 0x0F;

        // Calculate parity bits (assuming positions 1, 2, 4 are parity)
        int p1 = (data_bits & 0x05) + (data_bits & 0x0C); // Covers bits 2,4,6
        int p2 = (data_bits & 0x02) + (data_bits & 0x0C); // Covers bits 1,4,6
        int p3 = (data_bits & 0x01) + (data_bits & 0x03); // Covers bits 0,1,2

        // Place parity bits (convert integers 0/1 to bits)
        codeword[j++] = (p1 % 2) + '0';  
        codeword[j++] = (p2 % 2) + '0'; 
        codeword[j++] = data_bits & 0x08; // Extract and move data bit D3
        codeword[j++] = (p3 % 2) + '0';  
        codeword[j++] = data_bits & 0x04; 
        codeword[j++] = data_bits & 0x02;  
        codeword[j++] = data_bits & 0x01;
    }
}

void decode_hamming(const uint8_t *codeword, int codeword_length, uint8_t *data) {
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