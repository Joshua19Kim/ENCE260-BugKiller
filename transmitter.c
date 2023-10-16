/** @ random_number_generator.h
 *  @ Author: Jay Brydon
 *  @ 14 October 2023
 *  @ The code for the transmitter and receiver for the game.
*/

#include "transmitter.h"
#include "gameboard.h"
#include "system.h"
#include "ir_uart.h"
#include "usart1.h"
#include "timer0.h"
#include "prescale.h"

#include <stdint.h>

void transmitter_receiver_init (void)
{
    ir_uart_init ();
}

void send_my_kills (char my_kills)
{
    ir_uart_putc (my_kills);
}

bool ready_to_read (void)
{
    return ir_uart_read_ready_p ();
}

char get_opponent_kills (void)
{
    return ir_uart_getc ();
}

bool ready_to_write (void)
{
    return ir_uart_write_ready_p ();
}

void send_game_status (gstatus_t status)
{
    ir_uart_putc(status);
}

gstatus_t get_game_status (void)
{
    return ir_uart_getc ();   
}

void send_result(result_t result)
{
    ir_uart_putc(result);
}

result_t get_result (void)
{
    return ir_uart_getc ();   
}
