/** @ random_number_generator.h
 *  @ Author: Jay Brydon
 *  @ 14 October 2023
 *  @ The code for a linear congruential generator (LCG), which is a pseudorandom number generator.
*/

#ifndef RNG_H
#define RNG_H

#include "system.h"
#include <stdint.h>

void rng_counter_init ();

void set_seed ();

void set_modulus (uint8_t value);

void set_starting_lcg_value ();

void set_next_lcg_value ();

uint8_t get_next_random_number (uint8_t inputModulus);

#endif /* RNG_H */