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



void scrolling_screen (string letters) 
{
    tinygl_font_set(&font3x5_1);
    tinygl_text_dir_set(TINYGL_TEXT_DIR_ROTATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text(letters);
}

