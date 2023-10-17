/** @file    transmitter.c
 *  @authors Joshua Byoungsoo Kim (bki42), Jay Brydon (jbr268)
 *  @date    16 Oct 2023
 *  @brief   This contains the functions that control the functionality of the receiver and transmitter.
*/

#include "transmitter.h"
#include "gameboard.h"
#include "system.h"
#include "ir_uart.h"
#include "usart1.h"
#include "timer0.h"
#include "prescale.h"

#include <stdint.h>

/** Initialises the transmitter and the receiver. */
void transmitter_receiver_init(void)
{
    ir_uart_init();
}

/** Sends my total number of bugs killed to the opponent.
 * @param my_kills The total number of bugs I have killed.
*/
void send_my_kills(char my_kills)
{
    ir_uart_putc(my_kills);
}

bool ready_to_read(void)
{
    return ir_uart_read_ready_p();
}

char get_opponent_kills(void)
{
    return ir_uart_getc();
}

bool ready_to_write(void)
{
    return ir_uart_write_ready_p();
}

void send_game_status(gstatus_t status)
{
    ir_uart_putc(status);
}

gstatus_t get_game_status(void)
{
    return ir_uart_getc();   
}

void send_result(result_t result)
{
    ir_uart_putc(result);
}

result_t get_result(void)
{
    return ir_uart_getc();   
}
