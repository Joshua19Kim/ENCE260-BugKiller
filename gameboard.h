/** @file    gameboard.h
 *  @authors Joshua Byoungsoo Kim (bki42), Jay Brydon (jbr268)
 *  @date    10 October 2023
 *  @brief   it shows current game board status on LED matrix
*/

#ifndef GAMEBOARD_H
#define GAMEBOARD_H


#include "system.h"
#include "tinygl.h"

#define TOTAL_SPOTS 35
#define TOTAL_STAGE 3
#define INCR_RATE_BUGS 2
#define STARTING_NUM_BUGS 0


typedef struct killer_position
{
    tinygl_point_t pos;
} killer_t;

typedef struct bugs_position
{
    tinygl_point_t pos;
    bool status;
} bugs_t;

typedef enum game_status {
    START,
    READY,
    PLAYING,
    FINISHED,
    GAMEOVER
} gstatus_t;

typedef enum game_result {
    WINNER,
    LOSER,
    TIE
} result_t;


void nav_init(void);

void nav_update(void);

void killer_blink(killer_t);

int8_t bug_check(bugs_t*, uint8_t, tinygl_point_t);

void killer_move(bugs_t*, killer_t*, int8_t, int8_t);

uint8_t killer_control(bugs_t*, killer_t*, uint8_t);

void bugs_create(bugs_t*, uint8_t);



#endif /* GAMEBOARD.H */