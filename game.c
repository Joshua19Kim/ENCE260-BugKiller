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
static bool finished_first = 0;

int main (void)
{   
    system_init();
    nav_init();
    pacer_init (PACER_RATE);
    tinygl_init (PACER_RATE);
    tinygl_text_speed_set(MESSAGE_RATE);
    transmitter_receiver_init();
    
    screen_init("BUG KILLER");
    start_ready_screen(&my_game_status, &opponent_game_status);
    tinygl_init (PACER_RATE);


    uint16_t navswitch_tick = 0;
    uint16_t bugs_tick = 0;
    uint16_t killer_tick = 0;
    uint16_t receiving_tick = 0;
    
    bugs_t dots[TOTAL_SPOTS];
    

    /* set up the starting point of killer */
    killer_t killer;
    killer.pos.x = 2;
    killer.pos.y = 3;

    while (1) {
        
        pacer_wait ();
        tinygl_update ();

        /* killer blinking task*/
        if (killer_tick >= (PACER_RATE / KILLER_DOT_RATE-1)/2) {
            killer_tick = 0;
            /* make killer blinking*/
            killer_blink (killer);
        }
        /* navigation switch task*/
        if (navswitch_tick >= PACER_RATE / NAVSWITCH_RATE-1) {
            if (my_game_status == PLAYING) {
                navswitch_tick = 0;
                nav_update();
                my_bugs_killed += killer_control(dots, &killer, starting_bugs_num);
            }   
        }

        /* bugs task*/
        if (bugs_tick >= PACER_RATE / BUGS_RATE-1) {
            bugs_tick = 0;
            if (my_game_status == READY || my_game_status == FINISHED) {
                total_my_bugs_killed += my_bugs_killed;
                tinygl_init (PACER_RATE);
                starting_bugs_num += INCR_RATE_BUGS;
                bugs_create(dots, starting_bugs_num);
                current_stage++;
                my_bugs_killed = 0;
                my_game_status = PLAYING;
                opponent_game_status = PLAYING;
            } else if ((my_game_status == PLAYING) && (TOTAL_STAGE != current_stage)) {
                if (my_bugs_killed == starting_bugs_num) {
                    my_game_status = FINISHED;
                    if (ready_to_write())
                        send_game_status(FINISHED);
                }
            } else if ((my_game_status == PLAYING) && (TOTAL_STAGE == current_stage)) {
                if (my_bugs_killed == starting_bugs_num) {
                    my_game_status = GAMEOVER;
                    total_my_bugs_killed += my_bugs_killed;
                    if (ready_to_write())
                        send_game_status(GAMEOVER);
                    if (ready_to_write())
                        send_my_kills(total_my_bugs_killed);
                    finished_first = 1;
                    break;
                }
            }
        }
        if (receiving_tick >= PACER_RATE / RECEIVING_RATE - 1) {
            receiving_tick = 0;
            if (ready_to_read()) {
                opponent_game_status = get_game_status();
                if (opponent_game_status == GAMEOVER) {
                    opponent_bugs_killed = get_opponent_kills();
                    total_my_bugs_killed += my_bugs_killed;
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
                my_game_status = opponent_game_status;
            }
        }
        killer_tick++;
        navswitch_tick++;
        bugs_tick++;
        receiving_tick++;
    }

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

    final_screen(my_result);


    return 0;
}
