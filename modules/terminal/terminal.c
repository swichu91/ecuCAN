/*
 * terminal.c
 *
 *  Created on: 25 mar 2016
 *      Author: Mateusz
 */
#include "terminal.h"
#include "DbgTerminal.h"
#include "queue/queue.h"
#include "shell/shell.h"
#include "terminal_cmd.h"


static shell_t shell_usart;

static uint8_t terminal_write (char* str, size_t len)
{
	uint8_t i;

	for(i=0;i<len;i++){
		queue_enqueue(terminal_tx_queue, &str[i]);
	}

}

static uint8_t terminal_read(char* str)
{
	if (queue_front_and_dequeue(terminal_rx_queue, str) != QERR_OK) {

		*str = 0;
	}

}



void terminal_init(void) {
	terminal_tx_queue = queue_init(256, sizeof(uint8_t));
	terminal_rx_queue = queue_init(256, sizeof(uint8_t));

	DbgTerminal_SetColor(clRed, clBlack);

	shell_Init(&shell_usart,50);
	shell_RegisterCmdTab(&shell_usart,cmd_tab_usart,sizeof cmd_tab_usart / sizeof cmd_tab_usart[0]);
	shell_RegisterCodes(&shell_usart,TERMINAL_BS,TERMINAL_NEWLINE,TERMINAL_ARROW_LEFT,TERMINAL_ARROW_RIGHT,TERMINAL_ARROW_UP,TERMINAL_ARROW_DOWN);
	shell_RegisterFunctions(&shell_usart,terminal_write,terminal_read);


}

void terminal_RunPeriodic(void) {

	char rx_byte;
	char tx_byte;

	shell_RunPeriodic(&shell_usart);

	if (queue_front_and_dequeue(terminal_tx_queue, &tx_byte) == QERR_OK) {
		DbgTerminal_SendChar(tx_byte);
	}

}
