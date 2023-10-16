/** @file gameboard.c
 *  @author Joshua Byoungsoo Kim
 *  @date 10 October 2023
 *  @brief it shows current game board status on LED matrix
*/
#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "gameboard.h"
#include "tinygl.h"
#include "stdlib.h"
#include "random_number_generator.h"

static uint8_t killer_blink_flag = 0;

/** initialize navswitch*/
void nav_init (void) {
    navswitch_init ();
}

/** update navswitch*/
void nav_update (void) {
    navswitch_update ();
}

/** make killer point blinking
 * @param killer killer's location (x,y coordinate)
*/
void killer_blink (killer_t killer) {
    if (killer_blink_flag == 0) {
        tinygl_draw_point(killer.pos, 1);
        killer_blink_flag = 1;
    } else {
        tinygl_draw_point(killer.pos, 0);
        killer_blink_flag = 0;
    }
}

/** check whether the given spot is filled by a bug*/
int8_t bug_check (bugs_t *dots, uint8_t num, tinygl_point_t pos)
{
    for (uint8_t i = 0; i < num; i++)
    {
        if (dots[i].pos.x == pos.x
            && dots[i].pos.y == pos.y && dots[i].status)
            return i;
    }
    return -1;
}

/** change x,y coordinates of killer */
void killer_move (bugs_t *dots, killer_t *killer, int8_t dx, int8_t dy)
{
    tinygl_point_t n_pos;

    n_pos = tinygl_point (killer->pos.x + dx, killer->pos.y + dy);
    if ( bug_check (dots, TOTAL_SPOTS, killer->pos) != -1) {
        tinygl_draw_point (killer->pos,1);
    } else {
        tinygl_draw_point (killer->pos,0);
    } 
    killer->pos = n_pos;
    tinygl_draw_point (killer->pos, 1);
}

/** move killer position according to the navswitch control
    when navswitch is pushed, it will kill the bug if there is bug on that spot*/
uint8_t killer_control (bugs_t *bugs, killer_t *killer, uint8_t current_stage) {

    if (navswitch_push_event_p (NAVSWITCH_NORTH)) 
        killer_move(bugs, killer, 0,-1);
    if (navswitch_push_event_p (NAVSWITCH_SOUTH)) 
        killer_move(bugs, killer, 0,1);
    if (navswitch_push_event_p (NAVSWITCH_WEST))
        killer_move(bugs, killer, -1,0);
    if (navswitch_push_event_p (NAVSWITCH_EAST)) 
        killer_move(bugs, killer, 1,0);
    if (navswitch_push_event_p (NAVSWITCH_PUSH)) 
    {
        int8_t i = bug_check (bugs, current_stage, killer->pos);
        if ( i != -1 && bugs[i].status) {
            tinygl_draw_point (bugs[i].pos, 0);
            bugs[i].status = false;
            return 1;
        }
    }
    return 0;
}

/** create bugs on the LED matrix based on different stages */
void bugs_create (bugs_t *bugs, uint8_t stage)
{   
    for (uint8_t i = 0; i < TOTAL_SPOTS; i++) {
        for (uint8_t dx = 0; dx < TINYGL_WIDTH; dx++) {
            for (uint8_t dy = 0; dy < TINYGL_HEIGHT; dy++) {
                bugs[i].pos.x = dx;
                bugs[i].pos.y = dy;
                bugs[i].status = false;
            }
        }
    }

    for (uint8_t i = 0; i < stage; i++)
    {
        uint8_t x;
        uint8_t y;

        do {
            // x = get_next_random_number(TINYGL_WIDTH);
            // y = get_next_random_number(TINYGL_HEIGHT);

            x = rand () % TINYGL_WIDTH;
            y = rand () % TINYGL_HEIGHT;
        } while (bug_check (bugs, i, tinygl_point (x, y)) != -1);
        
        bugs[i].pos.x = x;
        bugs[i].pos.y = y;
        bugs[i].status = true;

        tinygl_draw_point (bugs[i].pos, 1);
    }
}

