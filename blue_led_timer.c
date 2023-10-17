/** @file    blue_led_timer.c
 *  @authors Joshua Byoungsoo Kim (bki42), Jay Brydon (jbr268)
 *  @date    17 Oct 2023
 *  @brief   The code that controls the functionality of the blue LED.
*/

#include "blue_led_timer.h"
#include "system.h"
#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>

static bool blue_led_is_on = false;

/** Initialises the blue LED. */
void blue_led_init(void)
{
    DDRC |= (1<<2);
}

/** Updates the rate at which the blue LED flashes when heading to the next stage (it flashes faster at higher stages).
 * @param current_stage The current stage, either 1, 2, or 3.
 * @param blue_led_rate The current blue LED rate, which'll be updated with this function.
*/
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

/** Turns the blue LED off. */
void blue_led_off(void)
{
    PORTC &= ~(1<<2);
}

/** Turns the blue LED on. */
void blue_led_on(void)
{
    PORTC |= (1<<2);
}

/** When this is called, it'll switch the the blue LED from being off to on (or vice versa). */
void blue_led_blink(void)
{
    if (blue_led_is_on) {
        blue_led_off();
        blue_led_is_on = false;
    } else {
        blue_led_on();
        blue_led_is_on = true;
    }
}
