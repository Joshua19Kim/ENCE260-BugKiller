/** @file   game.c
 *  @author Joshua Byoungsoo Kim, Jay Brydon
 *  @date   17 Oct 2023
 *  @brief  Implement the game 'Bug killer'
*/


#include "system.h"
#include "pacer.h"
#include "pio.h"
#include "lettershow.h"
#include "gameboard.h"
#include "navswitch.h"
#include "transmitter.h"
// #include "random_number_generator.h"



#define PACER_RATE 1000
#define MESSAGE_RATE 20
#define NAVSWITCH_RATE 200
#define BUGS_RATE 200
#define KILLER_DOT_RATE 5
#define RECEIVING_RATE 100


static char total_my_bugs_killed = 0;
static uint8_t my_bugs_killed = 0;
static char opponent_bugs_killed = 0;
static result_t my_result;
static gstatus_t my_game_status = START;
static gstatus_t opponent_game_status = START;
static uint8_t starting_bugs_num = STARTING_NUM_BUGS;
static uint8_t current_stage;
static bool finished_first = false;

/* main function to run game. */
int main (void)
{   
    /* Initialise system, navswitch, pacer, tinygl and ir_uart */
    system_init();
    nav_init();
    pacer_init (PACER_RATE);
    tinygl_init (PACER_RATE);
    tinygl_text_speed_set(MESSAGE_RATE);
    transmitter_receiver_init();
    
    /* Show the scrolling letters of Game title 'BUG KILLER', ready sign 'READY! and counting down number ' 
        it will go to next screen by pushing navswitch */
    screen_init("BUG KILLER");
    start_ready_screen(&my_game_status, &opponent_game_status);
    
    /* Initialise tinygl again for next screen */
    tinygl_init (PACER_RATE);

    /* Set ticks for different tasks in while loop with pacer */
    uint16_t navswitch_tick = 0;
    uint16_t bugs_field_tick = 0;
    uint16_t killer_tick = 0;
    uint16_t receiving_tick = 0;
    
    /* Set array containing each bugs' x,y coordinates */
    bugs_t dots[TOTAL_SPOTS];
    

    /* set up the starting point of killer */
    killer_t killer;
    killer.pos.x = 2;
    killer.pos.y = 3;

    /* While loop will be running until game status become GAMEOVER */
    while (1) {
        
        pacer_wait ();
        tinygl_update ();

        /* killer blinking task */
        if (killer_tick >= (PACER_RATE / KILLER_DOT_RATE-1)/2) {
            killer_tick = 0;
            /* make killer blinking*/
            killer_blink (killer);
        }
        /* navigation switch task */
        if (navswitch_tick >= PACER_RATE / NAVSWITCH_RATE-1) {
            if (my_game_status == PLAYING) {
                navswitch_tick = 0;
                nav_update();
                /* Once a player push navswitch when killer is sitting on a bug,
                    it will update the number of killed bugs in the stage, and
                    the bug will be off */
                my_bugs_killed += killer_control(dots, &killer, starting_bugs_num);
            }   
        }

        /* bugs field task */
        if (bugs_field_tick >= PACER_RATE / BUGS_RATE-1) {
            bugs_field_tick = 0;
            /* When the game status is READY or when the stages are FINISHED(except final stage),
                total number of killed bugs during game will be updated.
                the number of bugs for the next stage will be added by certain rate(INCR_RAGE_BUGS).
                The game status will be updated to PLAYING */
            if (my_game_status == READY || my_game_status == FINISHED) {
                tinygl_init (PACER_RATE);
                total_my_bugs_killed += my_bugs_killed;
                starting_bugs_num += INCR_RATE_BUGS;
                /* Create the bugs field for next stage. */
                bugs_create(dots, starting_bugs_num);
                current_stage++;
                my_bugs_killed = 0;
                my_game_status = PLAYING;
                opponent_game_status = PLAYING;

                /* When the game status is PLAYING but it is not final stage,
                    if a player kills same number of bugs with total number of bugs,
                    game status will be FINISHED and this status will be sent to the opponent */
            } else if ((my_game_status == PLAYING) && (TOTAL_STAGE != current_stage)) {
                if (my_bugs_killed == starting_bugs_num && ready_to_write()) {
                    my_game_status = FINISHED;
                    send_game_status(FINISHED);
                }

                /* When the game status is PLAYING and it is final stage,
                    if a player kills all the bugs in the stage,
                    game status will be GAMEOVER and this status will be sent to the oppoent
                    and total number of killed bugs will be sent as well. */
            } else if ((my_game_status == PLAYING) && (TOTAL_STAGE == current_stage)) {
                if (my_bugs_killed == starting_bugs_num) {
                    my_game_status = GAMEOVER;
                    total_my_bugs_killed += my_bugs_killed;
                    if (ready_to_write())
                        send_game_status(GAMEOVER);
                    if (ready_to_write())
                        send_my_kills(total_my_bugs_killed);
                    finished_first = true;
                    break;
                }
            }
        }
        /* receiving message task*/
        if (receiving_tick >= PACER_RATE / RECEIVING_RATE - 1) {
            receiving_tick = 0;
            /* Read the game status of opponent */
            if (ready_to_read()) {
                opponent_game_status = get_game_status();

                /* The player receives GAMEOVER status from opponent 
                    when the opponent kills all the bugs in the final stage 
                    before the player kills all.
                    The player also recieves */
                if (opponent_game_status == GAMEOVER) {
                    opponent_bugs_killed = get_opponent_kills();
                    total_my_bugs_killed += my_bugs_killed;
                    /* Compare player's total killed number with opponent's total number,
                        update my_result and send the result to the oppoent */
                    if (total_my_bugs_killed > opponent_bugs_killed) {
                        send_result(WINNER);
                        my_result = WINNER;
                    } else if (total_my_bugs_killed < opponent_bugs_killed) {
                        send_result(LOSER);
                        my_result = LOSER;
                    } else if (total_my_bugs_killed == opponent_bugs_killed){
                        send_result(TIE);
                        my_result = TIE;
                    }
                    break;
                }
                /* The player receive FINISH status from opponent
                    when the stage is not final stage*/
                my_game_status = opponent_game_status;
            }
        }
        /* Increment of ticks*/
        killer_tick++;
        navswitch_tick++;
        bugs_field_tick++;
        receiving_tick++;
    }
    /* If the player finishes the final stage first,
        receive the game result from opponent which is already calculated.
        Update my result.*/
    if (finished_first) {
        result_t opponent_result = get_result();
        if (opponent_result == WINNER) {
            my_result = LOSER;
        } else if (opponent_result == LOSER) {
            my_result = WINNER;
        } else if (opponent_result == TIE) {
            my_result = TIE;
        }
    }
    /* show the result on screen.*/
    final_screen(my_result);


    return 0;
}
