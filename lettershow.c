/** @file    scrollingstring.c
 *  @authors Joshua Byoungsoo Kim (bki42), Jay Brydon (jbr268)
 *  @date    10 October 2023
 *  @brief   it shows strings on LED matrix
*/

#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font3x5_1.h"
#include "lettershow.h"
#include "gameboard.h"
#include "navswitch.h"
#include "transmitter.h"

#define COUNTINGDOWN_MAX_TICK 2600

/** Initialise tinygl for scrolling letters 
 * @param letters string value that will be shown on player's screen
*/
void screen_init(string letters) 
{
    tinygl_font_set(&font3x5_1);
    tinygl_text_dir_set(TINYGL_TEXT_DIR_ROTATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text(letters);
}

/** Show Ready and counting down screen 
 * @param my_game_status the pointer of player's game status
 * @param opponent_game_status the pointer of opponent's game status
 */
void start_ready_screen(gstatus_t *my_game_status, gstatus_t *opponent_game_status) 
{
    int16_t countingdown_tick = -1;
    while(1) {   
        pacer_wait();
        tinygl_update();
        nav_update();

        /* When the player push navswitch shows sign 'READY!' on screen
            and send my game status to opponent */
        if (*my_game_status == START && navswitch_push_event_p (NAVSWITCH_PUSH)) {
            nav_init();
            tinygl_text("READY!");
            *my_game_status = READY;
            send_game_status(READY);
        /* When both players are READY, both screen starts counting down number 3, 2, 1 GO */
        } else if (*my_game_status == READY && *opponent_game_status == READY && countingdown_tick == -1) {
            tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
            tinygl_text("3 2 1 GO");
            countingdown_tick = 0;
        /* Control the time of letter "3 2 1 GO", otherwise it will repeat. */
        } else if (*my_game_status == READY && *opponent_game_status == READY && countingdown_tick <= COUNTINGDOWN_MAX_TICK) {
            countingdown_tick++;
        /* When it reaches the max tick, stop countingdown screen*/
        } else if (*my_game_status == READY && *opponent_game_status == READY && countingdown_tick > COUNTINGDOWN_MAX_TICK) {
            break;
        }
        /* Read the opponent game status */
        if (ready_to_read()) {
            *opponent_game_status = get_game_status();
        }
    }
}

/** Show the game result on player's screen
 * @param letters string value that will be shown on player's screen
 */
void final_scrolling_screen(string letters)
{
    screen_init(letters);

    while(1) {
        pacer_wait();
        tinygl_update();
        nav_update ();
    }
}

/** Check my game result and show it on player's screen 
 * @param my_result final game result of the player
*/
void final_screen(result_t my_result)
{
    if (my_result == WINNER) {
        final_scrolling_screen("WIN!");
    } else if (my_result == LOSER) {
        final_scrolling_screen("LOSE!");
    } else if (my_result == TIE) {
        final_scrolling_screen("TIE!");
    }
}