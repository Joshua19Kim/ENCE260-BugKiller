/** @file    gameboard.h
 *  @authors Joshua Byoungsoo Kim (bki42), Jay Brydon (jbr268)
 *  @date    10 Oct 2023
 *  @brief   it shows current game board status on LED matrix
*/


#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "system.h"
#include "tinygl.h"

#define TOTAL_SPOTS 35
#define TOTAL_STAGE 3
#define INCR_RATE_BUGS 3
#define STARTING_NUM_BUGS 0


/**
 * Killer position with x,y coordinates structure
*/
typedef struct killer_position
{
    tinygl_point_t pos;
} killer_t;

/**
 * Bugs position with x,y coordinates structure
*/
typedef struct bugs_position
{
    tinygl_point_t pos;
    bool status;
} bugs_t;

/**
 * enum for options of game status
*/
typedef enum game_status {
    START,
    READY,
    PLAYING,
    FINISHED,
    GAMEOVER
} gstatus_t;

/**
 * enum for options of final game results
*/
typedef enum game_result {
    WINNER,
    LOSER,
    TIE
} result_t;


/** Initialize navswitch*/
void nav_init(void);

/** Update navswitch*/
void nav_update(void);

/** Make killer point blinking
 * @param killer killer's location (x,y coordinate)
*/
void killer_blink(killer_t);

/** Check whether the given spot is filled by a bug
 * return index number of array of bugs if there is bug
 * return -1 if there is no bug
 * @param dots the pointer for the array of the each bug position(x,y coordinates)
 * @param total_bug_num the total number of bugs in the stage
 * @param pos the coordinates(x,y) that want to be check
*/
int8_t bug_check(bugs_t*, uint8_t, tinygl_point_t);

/** Change x,y coordinates of killer
 * @param dots the pointer for the array of the each bug position(x,y coordinates)
 * @param killer the pointer for the player's location as x,y coordinates
 * @param dx x coordinate that player wants to move
 * @param dy y coordinate that player wants to move
 */
void killer_move(bugs_t*, killer_t*, int8_t, int8_t);


/** 
 * Move killer position according to the navswitch control when navswitch is pushed, 
 * it will kill the bug if there is bug on that spot
 * @param bugs the pointer for the array of the each bug position(x,y coordinates)
 * @param killer the pointer for the player's location as x,y coordinates
 * @param total_bug_num the total bugs number that the player start with in the stage
 */
uint8_t killer_control(bugs_t*, killer_t*, uint8_t);

/** create bugs on the LED matrix based on different stages 
 * @param bugs the pointer for the array of the each bug position(x,y coordinates)
 * @param total_bug_num the total bugs number that the player start with in the stage
*/
void bugs_create(bugs_t*, uint8_t);

#endif /* GAMEBOARD.H */
