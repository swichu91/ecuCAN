/*
 * terminal.c
 *
 *  Created on: 25 mar 2016
 *      Author: Mateusz
 */
#include "terminal.h"
#include "DbgTerminal.h"
#include "queue/queue.h"

void terminal_init(void) {
	terminal_tx_queue = queue_init(256, sizeof(uint8_t));
	terminal_rx_queue = queue_init(256, sizeof(uint8_t));

	DbgTerminal_SetColor(clRed, clBlack);

}

void terminal_RunPeriodic(void) {

	char rx_byte;
	char tx_byte;

	if (queue_front_and_dequeue(terminal_rx_queue, &rx_byte) == QERR_OK) {
		queue_enqueue(terminal_tx_queue, &rx_byte);
	}

	if (queue_front_and_dequeue(terminal_tx_queue, &tx_byte) == QERR_OK) {
		DbgTerminal_SendChar(tx_byte);
	}

}
