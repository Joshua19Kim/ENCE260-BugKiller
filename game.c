#include "system.h"
#include "pacer.h"
#include "pio.h"
#include "scrollstring.h"
#include "gameboard.h"
#include "navswitch.h"



#define PACER_RATE 1000
#define MESSAGE_RATE 20
#define NAVSWITCH_RATE 200
#define BUGS_RATE 200
#define KILLER_DOT_RATE 5

static uint16_t bugs_killed;
static uint8_t game_status = READY;
static uint8_t starting_bugs_num = STARTING_NUM_BUGS;
static uint8_t current_stage;

int main (void)
{   
    system_init();
    nav_init();
    pacer_init (PACER_RATE);
    tinygl_init (PACER_RATE);
    tinygl_text_speed_set(MESSAGE_RATE);
    
    scrolling_screen("READY?");
    
    // countingdown();
    while(1)
    {
        pacer_wait();
        tinygl_update();
        nav_update ();

        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            nav_init ();
            tinygl_init (PACER_RATE);
            break;
        }
    }

    uint16_t navswitch_tick = 0;
    uint16_t bugs_tick = 0;
    uint16_t killer_tick = 0;
    
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
            if (game_status == PLAYING) {
                navswitch_tick = 0;
                nav_update();
                bugs_killed = killer_control(dots, &killer, starting_bugs_num, bugs_killed);
            }   
        }

        /* bugs task*/
        if (bugs_tick >= PACER_RATE / BUGS_RATE-1) {
            bugs_tick = 0;
            if (game_status == READY) {
                bugs_create(dots, starting_bugs_num);
                current_stage++;
                game_status = PLAYING;
                bugs_killed = 0;
            } else if ((game_status == PLAYING) && (TOTAL_STAGE != current_stage)) {
                if (bugs_killed == starting_bugs_num) {
                    game_status = READY;
                    starting_bugs_num += INCR_RATE_BUGS;
                }
            } else if ((game_status == PLAYING) && (TOTAL_STAGE == current_stage)) {
                if (bugs_killed == starting_bugs_num) {
                    game_status = GAMEOVER;
                    break;
                }
            }
        }
        killer_tick++;
        navswitch_tick++;
        bugs_tick++;
    }
    scrolling_screen("GAMEOVER");

    return 0;
}
