/** @ scrollingstring.c
 *  @ author Joshua Byoungsoo Kim
 *  @ 10 October 2023
 *  @ it shows strings on LED matrix
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


void screen_init (string letters) 
{
    tinygl_font_set(&font3x5_1);
    tinygl_text_dir_set(TINYGL_TEXT_DIR_ROTATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text(letters);
}

void start_ready_screen(gstatus_t *my_game_status, gstatus_t *opponent_game_status) 
{
    int16_t countingdown_tick = -1;
    while(1)
    {
        pacer_wait();
        tinygl_update();
        nav_update ();
        
        if (*my_game_status == START && navswitch_push_event_p (NAVSWITCH_PUSH)) {
            nav_init ();
            tinygl_text("READY!");
            *my_game_status = READY;
            send_game_status(READY);
        } else if (*my_game_status == READY && *opponent_game_status == READY && countingdown_tick == -1) {
            tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
            tinygl_text("3 2 1 GO");
            countingdown_tick = 0;
        } else if (*my_game_status == READY && *opponent_game_status == READY && countingdown_tick <= COUNTINGDOWN_MAX_TICK){
            countingdown_tick++;
        } else if (*my_game_status == READY && *opponent_game_status == READY && countingdown_tick > COUNTINGDOWN_MAX_TICK){
            break;
        }
        if (ready_to_read()) {
            *opponent_game_status = get_game_status();
        }
    }
}

void final_scrolling_screen(string letters)
{
    screen_init (letters);
    while(1)
    {
        pacer_wait();
        tinygl_update();
        nav_update ();
    }
}

void final_screen (char my_bugs_killed, char opponent_bugs_killed)
{
    if (my_bugs_killed > opponent_bugs_killed) {
        // YOU WIN!
        final_scrolling_screen("YOU WIN!");
    } else if (opponent_bugs_killed > my_bugs_killed) {
        // YOU LOSE!
        final_scrolling_screen("YOU LOSE!");
    } else {
        // TIE!
        final_scrolling_screen("TIE!");
    }

}