#include "system.h"
#include "pacer.h"
#include "pio.h"
#include "scrollstring.h"
#include "gameboard.h"

int main (void)
{
    system_init();

    scrolling_screen("READY?");
    countingdown();
    
    board_init ();


    return 0;
}
