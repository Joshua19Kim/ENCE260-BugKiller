/** @file   random_number_generator.h
 *  @authors Joshua Byoungsoo Kim (bki42), Jay Brydon (jbr268)
 *  @date   14 October 2023
 *  @brief  The code for a linear congruential generator (LCG), which is a pseudorandom number generator.
*/

#ifndef RANDOM_NUMBER_GENERATOR_H
#define RANDOM_NUMBER_GENERATOR_H

#include <stdint.h>

/** Sets the modulus, which'll either be 5 or 7. 
 * This is due to the fact that the LED screen is 5 columns by 7 rows.
 * @param modulusInput The modulus that will be used in the LCG.
*/
void set_modulus(uint8_t modulusInput);

/** Sets the seed as the value from the counter.
 * This allows for different sets of pseudorandom numbers each time.
*/
void set_seed(void);

/** Sets the first value of the LCG (which will not be used as a random number). */
void set_starting_lcg_value(void);

/** Sets currentRandomNumber to the next LCG value. */
void set_next_lcg_value(void);

/** Returns the next LCG value (which is used as a random number). 
 * Combines everything into one function too.
 * @param modulusInput The modulus that will be used in the LCG. This is parsed into the function above.
*/
uint8_t get_next_random_number(uint8_t modulusInput);

#endif /* RANDOM_NUMBER_GENERATOR_H */
