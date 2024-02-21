#ifndef LASER_TRANSMIT
#define LASER_TRANSMIT

// Define bit duration and inter-bit delay in ms
#define BIT_DURATION 40
#define INTER_BIT_DELAY 10

#include <stdbool.h>

// Laser transmittion functions
void transmit_bit(bool bit_state);
void transmit_byte(char data);
void transmit_message(char message);

#endif