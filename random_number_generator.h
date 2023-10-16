/** @ random_number_generator.h
 *  @ Author: Jay Brydon
 *  @ 14 October 2023
 *  @ The code for a linear congruential generator (LCG), which is a pseudorandom number generator.
*/

#ifndef RANDOM_NUMBER_GENERATOR_H
#define RANDOM_NUMBER_GENERATOR_H

#include "system.h"

void rng_counter_init (void);

void set_seed (void);

void set_modulus (uint8_t value);

void set_starting_lcg_value (void);

void set_next_lcg_value (void);

uint8_t get_next_random_number (uint8_t);

#endif /* RANDOM_NUMBER_GENERATOR_H */
