#include <stdio.h>
#include <string.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"

// LINDA Libraries
#include "encoding.h"
#include "laser_transmit.h"


const uint led_pin = 25;
const uint laser_pin = 16;
const uint rgb_pin = 8;

// Set up GPIO etc
void setup() {
    gpio_init(led_pin);
    gpio_init(laser_pin);
    gpio_init(rgb_pin);

    gpio_set_dir(led_pin, GPIO_OUT);
    gpio_set_dir(laser_pin, GPIO_IN);
    gpio_set_dir(rgb_pin, GPIO_OUT);
}

int main() {
    // Initialize controller pins
    setup();

    // Initialize chosen serial port
    stdio_init_all();

    // Example data to transmit over laser link
    const char *send_data = "Hello world!";
    int data_length = strlen(send_data);

    int encoded_length = (data_length * 7 + 3) / 4;
    uint8_t encoded_data[encoded_length];

    encode_hamming7_4((const uint8_t *)send_data, data_length, encoded_data);
    printf(encoded_data);

    // Loop forever
    while (true) {
        // Laser signal is HIGH when no laser detected, LOW when laser detected
        if(!gpio_get(laser_pin)) {
            gpio_put(led_pin, true);
            // printf("AH!\n");
        } else {
            gpio_put(led_pin, false);
            // printf("Nothing\n"); 
        }
        sleep_ms(50);
    }
}