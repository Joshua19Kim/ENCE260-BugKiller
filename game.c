#include "system.h"
#include "pacer.h"
#include "pio.h"
#include "scrollstring.h"
#include "gameboard.h"
#include "random_number_generator.h"

int main (void)
{
    system_init();

    scrolling_screen("READY?");
    countingdown();
    
    board_init ();

    temp_func()

    return 0;
}
