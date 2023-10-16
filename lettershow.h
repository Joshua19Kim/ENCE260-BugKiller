/** @ lettershow.h
 *  @ author Joshua Byoungsoo Kim
 *  @ 10 October 2023
 *  @ it shows strings on LED matrix
*/

#ifndef LETTERSHOW_H
#define LETTERSHOW_H

#include "gameboard.h"



typedef char string[];

void screen_init (string) ;

void start_ready_screen(gstatus_t *, gstatus_t *) ;

void final_scrolling_screen(string) ;

void final_screen (char , char);

#endif /* LETTERSHOW_H */