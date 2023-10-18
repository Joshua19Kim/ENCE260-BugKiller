/** @file    blue_led_timer.h
 *  @authors Joshua Byoungsoo Kim (bki42), Jay Brydon (jbr268)
 *  @date    17 Oct 2023
 *  @brief   The code that controls the functionality of the blue LED.
*/

#ifndef BLUE_LED_TIMER_H
#define BLUE_LED_TIMER_H

#include <stdint.h>

/** Initialises the blue LED. */
void blue_led_init(void);

/** Updates the rate at which the blue LED flashes when heading to the next stage (it flashes faster at higher stages).
 * @param current_stage The current stage, either 1, 2, or 3.
 * @param blue_led_rate The current blue LED rate, which'll be updated with this function.
*/
uint8_t led_rate_update(uint8_t current_stage, uint8_t blue_led_rate);

/** Turns the blue LED off. */
void blue_led_off(void);

/** Turns the blue LED on. */
void blue_led_on(void);

/** When this is called, it'll switch the the blue LED from being off to on (or vice versa). */
void blue_led_blink(void);

#endif /* BLUE_LED_TIMER_H */
