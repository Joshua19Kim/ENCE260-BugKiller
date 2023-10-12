/** @ gameboard.c
 *  @ author Joshua Byoungsoo Kim
 *  @ 10 October 2023
 *  @ it shows current game board status on LED matrix
*/
#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "gameboard.h"
#include "tinygl.h"
#include "stdlib.h"

#define TOTAL_STAGE 3
#define TOTAL_DOTS 35
#define INCR_DOTS 2
#define STARTING_NUM_DOTS 2

#define PACER_RATE 1000
#define NAVSWITCH_RATE 200
#define MAP_RATE 200
#define PLAYER_DOT_RATE 5


static uint16_t clicked_dots;
static uint8_t game_status = READY;
static uint8_t current_total_dots = STARTING_NUM_DOTS;
static uint8_t current_stage;

// static uint8_t winning_score;

void nav_init (void) {
    navswitch_init ();
}

void nav_update (void) {
    navswitch_update ();
}

int8_t dot_check (dots_t *dots, uint8_t num, tinygl_point_t pos)
{
    for (uint8_t i = 0; i < num; i++)
    {
        if (dots[i].pos.x == pos.x
            && dots[i].pos.y == pos.y && dots[i].status)
            return i;
    }
    return -1;
}

void player_move (dots_t *dots, player_t *player, int8_t dx, int8_t dy)
{
    tinygl_point_t n_pos;

    n_pos = tinygl_point (player->pos.x + dx, player->pos.y + dy);
    if ( dot_check (dots, TOTAL_DOTS, player->pos) != -1) {
        tinygl_draw_point (player->pos,1);
    } else {
        tinygl_draw_point (player->pos,0);
    } 
    player->pos = n_pos;
    tinygl_draw_point (player->pos, 1);
}

void nav_control (dots_t *dots, player_t *player, uint8_t current_stage) {

    if (navswitch_push_event_p (NAVSWITCH_NORTH)) 
        player_move(dots, player, 0,-1);
    if (navswitch_push_event_p (NAVSWITCH_SOUTH)) 
        player_move(dots, player, 0,1);
    if (navswitch_push_event_p (NAVSWITCH_WEST))
        player_move(dots, player, -1,0);
    if (navswitch_push_event_p (NAVSWITCH_EAST)) 
        player_move(dots, player, 1,0);
    if (navswitch_push_event_p (NAVSWITCH_PUSH)) 
    {
        int8_t i = dot_check (dots, current_stage, player->pos);
        if ( i != -1 && dots[i].status) {
            tinygl_draw_point (dots[i].pos, 0);
            dots[i].status = false;
            clicked_dots++;
        }
    }
}

void dots_create (dots_t *dots, uint8_t stage)
{   
    for (uint8_t i = 0; i < TOTAL_DOTS; i++) {
        for (uint8_t dx = 0; dx < TINYGL_WIDTH; dx++) {
            for (uint8_t dy = 0; dy < TINYGL_HEIGHT; dy++) {
                dots[i].pos.x = dx;
                dots[i].pos.y = dy;
                dots[i].status = false;
            }
        }
    }

    for (uint8_t i = 0; i < stage; i++)
    {
        uint8_t x;
        uint8_t y;

        do {
            x = rand () % TINYGL_WIDTH;
            y = rand () % TINYGL_HEIGHT;
        } while (dot_check (dots, i, tinygl_point (x, y)) != -1);
        
        dots[i].pos.x = x;
        dots[i].pos.y = y;
        dots[i].status = true;

        tinygl_draw_point (dots[i].pos, 1);
    }
}




void temp_work (void) {
    
    system_init ();
    pacer_init (PACER_RATE);
    uint16_t navswitch_tick = 0;
    uint16_t map_tick = 0;
    uint16_t player_tick = 0;
    uint8_t blink_flag = 0;
    nav_init();
    tinygl_init (PACER_RATE);

    dots_t dots[TOTAL_DOTS];
    

    /* set up the starting point of player */
    player_t player;
    player.pos.x = 2;
    player.pos.y = 3;

    while (1) {
        
        pacer_wait ();
        tinygl_update ();

        if (player_tick >= (PACER_RATE / PLAYER_DOT_RATE-1)/2) {
            player_tick = 0;
            /* make the dot that this player moves blinking*/
            if (blink_flag == 0){
                tinygl_draw_point(player.pos, 1);
                blink_flag = 1;
            } else {
                tinygl_draw_point(player.pos, 0);
                blink_flag = 0;
            }
        }

        if (navswitch_tick >= PACER_RATE / NAVSWITCH_RATE-1) {

            if (game_status == PLAYING) {
                navswitch_tick = 0;
                nav_update();
                nav_control(dots, &player, current_total_dots);
            }   
        }

        if (map_tick >= PACER_RATE / MAP_RATE-1) {
            map_tick = 0;
            if (game_status == READY) {
                dots_create(dots, current_total_dots);
                current_stage++;
                game_status = PLAYING;
                clicked_dots = 0;
            } else if ((game_status == PLAYING) && (TOTAL_STAGE != current_stage)) {
                if (clicked_dots == current_total_dots) {
                    game_status = READY;
                    current_total_dots += INCR_DOTS;
                }
            } else if ((game_status == PLAYING) && (TOTAL_STAGE == current_stage)) {
                if (clicked_dots == current_total_dots) {
                    game_status = GAMEOVER;
                    break;
                }
            }
        }
        player_tick++;
        navswitch_tick++;
        map_tick++;
    }
}

