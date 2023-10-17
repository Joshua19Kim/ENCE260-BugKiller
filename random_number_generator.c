/** @file    random_number_generator.c
 *  @authors Joshua Byoungsoo Kim (bki42), Jay Brydon (jbr268)
 *  @date    14 October 2023
 *  @brief   The code for a linear congruential generator (LCG), which is a pseudorandom number generator.
*/

#include "random_number_generator.h"
//#include "system.h"
//#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>

/** Parameters for the LCG */
#define MULTIPLIER 36
#define INCREMENT 11

/** The seed for the LCG (will use the TCNT1 value as the seed). */
static uint8_t seed;
/** The modulus used in the LCG. */
static uint8_t modulus;
/** Holds the current LCG value, which is used for the game. */
static uint8_t currentRandomNumber;
/** Whether the starting value of the LCG has been generated or not. */
static bool got_starting_value = 0;

/** Sets the modulus, which'll either be 5 or 7. 
 * This is due to the fact that the LED screen is 5 columns by 7 rows.
 * @param modulusInput The modulus that will be used in the LCG.
*/
void set_modulus(uint8_t modulusInput)
{
    modulus = modulusInput;
}

/** Sets the seed as the value from the counter.
 * This allows for different sets of pseudorandom numbers each time.
*/
void set_seed(void)
{
    seed = 1234 % modulus;
}

/** Sets the first value of the LCG (which will not be used as a random number). */
void set_starting_lcg_value(void)
{
    currentRandomNumber = seed;
}

/** Sets currentRandomNumber to the next LCG value. */
void set_next_lcg_value(void)
{
    uint8_t newRandomNumber;
    newRandomNumber = (MULTIPLIER * currentRandomNumber + INCREMENT) % modulus;
    currentRandomNumber = newRandomNumber;
}

/** Returns the next LCG value (which is used as a random number). 
 * Combines everything into one function too.
*/
uint8_t get_next_random_number(uint8_t modulusInput)
{
    if (!got_starting_value) {
        set_modulus(modulusInput);
        set_seed();
        set_starting_lcg_value();
        got_starting_value = 1;
    }
    set_next_lcg_value ();
    return currentRandomNumber;
}
