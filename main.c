#include <stdio.h>
#include <string.h>

#include "pico/stdlib.h"

// LINDA Libraries
#include "include/encoding.h"
#include "include/laser_transmit.h"


const uint led_pin = 25;
const uint rx_pin = 16;
const uint tx_pin = 17;
const uint switch_pin = 18;

const char *message = "Hello world!";

// Set up GPIO etc
void setup() {
    gpio_init(led_pin);
    gpio_init(rx_pin);
    gpio_init(tx_pin);
    gpio_init(switch_pin);

    gpio_set_dir(led_pin, GPIO_OUT);
    gpio_set_dir(tx_pin, GPIO_OUT);
    gpio_set_dir(rx_pin, GPIO_IN);
    gpio_set_dir(switch_pin, GPIO_IN);
}

int main() {
    // Initialize controller pins and serial port
    setup();

    stdio_init_all();    

    // Loop forever
    while (true) {
        printf("Hello!");
        // Check switch_pin to see if we're in Tx or Rx mode
        if(!gpio_get(switch_pin)) {
            // Transmit mode
            // Example data to transmit over laser link
            int message_length = strlen(message);
            uint8_t codeword[message_length * 7]; // Worst case each char takes 7 bits of codeword
            encode_hamming7_4(message, message_length, codeword);
            printf("Message: %s\nLength: %d\nint8_t encoded data: %u\n", message, message_length, codeword);
        } else {
            // Receive mode
            // Laser signal is HIGH when no laser detected, LOW when laser detected
            if(!gpio_get(rx_pin)) {
                gpio_put(led_pin, true);
                // printf("AH!\n");
            } else {
                gpio_put(led_pin, false);
                // printf("Nothing\n"); 
            }
            sleep_ms(50);
        }
    }
}