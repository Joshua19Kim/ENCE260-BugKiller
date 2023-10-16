/** @ random_number_generator.h
 *  @ Author: Jay Brydon
 *  @ 14 October 2023
 *  @ The code for the transmitter and receiver for the game.
*/

#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include "gameboard.h"

void transmitter_receiver_init (void);

bool ready_to_read (void);

void send_my_kills (char);

bool ready_to_write (void);

char get_opponent_kills (void);

void send_game_status (gstatus_t);

gstatus_t get_game_status (void);

#endif /* TRANSMITTER_H */