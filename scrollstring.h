/** @ scrollingstring.h
 *  @ author Joshua Byoungsoo Kim
 *  @ 10 October 2023
 *  @ it shows strings on LED matrix
*/

#ifndef SCROLLSTRING_H
#define SCROLLSTRING_H

#include "gameboard.h"



typedef char string[];

void screen_init (string) ;

void start_ready_screen(gstatus_t *my_game_status, gstatus_t *opponent_game_status) ;

void final_scrolling_screen(string) ;

#endif /* SCROLLSTRING_H */