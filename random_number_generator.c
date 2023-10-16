/** @ random_number_generator.h
 *  @ Author: Jay Brydon
 *  @ 14 October 2023
 *  @ The code for a linear congruential generator (LCG), which is a pseudorandom number generator.
*/

#include "random_number_generator.h"
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>

#define MULTIPLIER 36 /* Parameters for the LCG. */
#define INCREMENT 11

static uint32_t seed;
static uint8_t modulus;   /* The modulus used in the generator. */
static uint8_t currentRandomNumber;
static bool got_starting_value = 0; /* Whether the starting value has been generated or not. */

void rng_counter_init (void)
{
    /* Initialises the counter used to get the seed value. */
    TCCR1A = 0x00;
    TCCR1B = 0x05;
    TCCR1C = 0x00;
}

void set_modulus (uint8_t value)
{
    /* Sets the modulus, which'll either be 5 or 7.
       This is due to the fact that the LED screen is 5 by 7. */
    modulus = value;
}

void set_seed (void)
{
    /* Sets the seed as the value from the counter.
       This allows for different sets of pseudorandom numbers each time. */
    seed = TCNT1 % modulus;
}

void set_starting_lcg_value (void)
{
    /* Sets the first value of the LCG (which will not be used as a random number). */
    currentRandomNumber = seed;
}

void set_next_lcg_value (void)
{
    /* Sets currentRandomNumber to the next LCG value. */
    currentRandomNumber = (MULTIPLIER * currentRandomNumber + INCREMENT) % modulus;
}

uint8_t get_next_random_number (uint8_t inputModulus)
{
    /* Returns the next LCG value (which is used as a random number). 
       Combines everything into one function too. */
    if (!got_starting_value) {
        rng_counter_init();
        set_modulus(inputModulus);
        set_seed();
        set_starting_lcg_value();
        got_starting_value = 1;
    }
    set_next_lcg_value ();
    return currentRandomNumber;
}
