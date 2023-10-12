/** @ gameboard.h
 *  @ author Joshua Byoungsoo Kim
 *  @ 10 October 2023
 *  @ it shows current game board status on LED matrix
*/

#ifndef GAMEBOARD_H
#define GAMEBOARD_H


#include "system.h"
#include "tinygl.h"

typedef struct player_position
{
    tinygl_point_t pos;
} player_t;

typedef struct dots_position
{
    tinygl_point_t pos;
    bool status;
} dots_t;

typedef enum game_status {
    READY,
    PLAYING,
    GAVEOVER
} gstatus_t;

typedef enum stage_level{
    FIRST_STAGE = 8,
    SECOND_STAGE = 18,
    THIRD_STAGE = 25

} stage_t;




void nav_init (void) ;

void nav_update (void) ;


int8_t dot_check (dots_t*, uint8_t, tinygl_point_t) ;

void player_move (dots_t*, player_t*, int8_t, int8_t) ;

void nav_control (dots_t*, player_t*) ;

void dots_create (dots_t*, stage_t) ;


void temp_work (void) ;



#endif /* GAMEBOARD.H */