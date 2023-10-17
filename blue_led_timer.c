/** @ random_number_generator.h
 *  @ Author: Jay Brydon
 *  @ 14 October 2023
 *  @ The code for the timer that controls the rate at which the blue LED flashes.
*/

#include "blue_led_timer.h"
#include "system.h"
#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>

static bool blue_led_flag = false;

void blue_led_init(void)
{
    DDRC |= (1<<2);
}

uint8_t led_rate_update(uint8_t current_stage, uint8_t blue_led_rate)
{   
    uint8_t new_blue_led_rate;
    if (current_stage == 1) {
        new_blue_led_rate = blue_led_rate;
    } else if (current_stage == 2) {
        new_blue_led_rate = blue_led_rate * 2;
    } else {
        new_blue_led_rate = blue_led_rate * 3 / 2;
    }
    return new_blue_led_rate;
}

void blue_led_off(void)
{
    PORTC &= ~(1<<2);
}

void blue_led_on(void)
{
    PORTC |= (1<<2);
}

void blue_led_blink(void)
{
    if (blue_led_flag) {
        blue_led_off();
        blue_led_flag = false;
    } else {
        blue_led_on();
        blue_led_flag = true;
    }
}
