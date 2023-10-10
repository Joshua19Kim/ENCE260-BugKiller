/** @ gameboard.c
 *  @ author Joshua Byoungsoo Kim
 *  @ 10 October 2023
 *  @ it shows current game board status on LED matrix
*/
#include "system.h"
#include "pacer.h"
#include "pio.h"
#include "navswitch.h"
#include "gameboard.h"

void board_init () 
{
    pio_config_set(LEDMAT_COL1_PIO,PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_COL2_PIO,PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_COL3_PIO,PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_COL4_PIO,PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_COL5_PIO,PIO_OUTPUT_HIGH);
    
    pio_config_set(LEDMAT_ROW1_PIO,PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_ROW2_PIO,PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_ROW3_PIO,PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_ROW4_PIO,PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_ROW5_PIO,PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_ROW6_PIO,PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_ROW7_PIO,PIO_OUTPUT_HIGH);

}