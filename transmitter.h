/** @file   random_number_generator.h
 *  @author Jay Brydon
 *  @date   14 October 2023
 *  @brief  The code for the transmitter and receiver for the game.
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

void send_result(result_t);

result_t get_result (void);

#endif /* TRANSMITTER_H */