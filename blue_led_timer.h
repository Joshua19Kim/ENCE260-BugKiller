/** @ random_number_generator.h
 *  @ Author: Jay Brydon (jbr268), Joshua Byoungsoo Kim (bki42)
 *  @ 14 October 2023
 *  @ The code for the timer that controls the rate at which the blue LED flashes.
*/

#ifndef BLUE_LED_TIMER_H
#define BLUE_LED_TIMER_H

#include <stdint.h>

void blue_led_init(void);

uint8_t led_rate_update(uint8_t current_stage, uint8_t blue_led_rate);

void blue_led_off(void);

void blue_led_on(void);

void blue_led_blink(void);

#endif /* BLUE_LED_TIMER_H */
