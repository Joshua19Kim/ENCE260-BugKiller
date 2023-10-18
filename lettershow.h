/** @file    lettershow.h
 *  @authors Joshua Byoungsoo Kim (bki42), Jay Brydon (jbr268)
 *  @date    10 Oct 2023
 *  @brief   It shows strings on LED matrix
*/


#ifndef LETTERSHOW_H
#define LETTERSHOW_H

#include "gameboard.h"

typedef char string[];

/** Initialise tinygl for scrolling letters 
 * @param letters string value that will be shown on player's screen
*/
void screen_init(string letters);

/** Show Ready and counting down screen 
 * @param my_game_status the pointer of player's game status
 * @param opponent_game_status the pointer of opponent's game status
 */
void start_ready_screen(gstatus_t *my_game_status, gstatus_t *opponent_game_status);

/** Show the game result on player's screen
 * @param letters string value that will be shown on player's screen
 */
void final_scrolling_screen(string letters);

/** Check my game result and show it on player's screen 
 * @param my_result final game result of the player
*/
void final_screen(result_t my_result);

#endif /* LETTERSHOW_H */
