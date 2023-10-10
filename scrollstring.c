/** @ scrollingstring.c
 *  @ author Joshua Byoungsoo Kim
 *  @ 10 October 2023
 *  @ it shows strings on LED matrix
*/

#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font3x5_1.h"
#include "scrollstring.h"
#include "navswitch.h"

#define PACER_RATE 500
#define MESSAGE_RATE 10


void tinygl_start (void)
{
    /* Initialise tinygl. */
    tinygl_init(PACER_RATE);
    tinygl_font_set(&font3x5_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_dir_set(TINYGL_TEXT_DIR_ROTATE);

}

void scrolling_screen (string letters) 
{
    tinygl_start ();
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    
    tinygl_text(letters);
    pacer_init (PACER_RATE);
    navswitch_init ();

    while(1)
    {
        pacer_wait();
        
        tinygl_update();
        navswitch_update ();

        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            navswitch_init ();
            break;
        }
    }

}

void countingdown (void)
{
    tinygl_start ();
    tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
    tinygl_text("3 2 1 GO");
    pacer_init (PACER_RATE);
    uint16_t flag = 0;
    while(1)
    {
        pacer_wait();
        tinygl_update();
        flag++;
        if (flag > 2600) {
            break;
        }
    }
}