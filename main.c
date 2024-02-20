#include <stdio.h>
#include <hardware/gpio.h>
#include "pico/stdlib.h"
#include "lib/encoding.h"
#include "lib/laser_transmit.h"


const uint led_pin = 25;
const uint laser_pin = 22;

// Set up GPIO etc
void setup() {
    gpio_init(led_pin);
    gpio_init(laser_pin);

    gpio_set_dir(led_pin, GPIO_OUT);
    gpio_set_dir(laser_pin, GPIO_IN);
}

int main() {
    // Initialize controller pins
    setup();

    // Initialize chosen serial port
    stdio_init_all();

    // Loop forever
    while (true) {
        // Laser signal is HIGH when no laser detected, LOW when laser detected
        if(!gpio_get(laser_pin)) {
            gpio_put(led_pin, true);
            printf("AH!\n");
        } else {
            gpio_put(led_pin, false);
            printf("Nothing\n"); 
        }
        sleep_ms(50);
    }
}