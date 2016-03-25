/*
 * terminal.h
 *
 *  Created on: 25 mar 2016
 *      Author: Mateusz
 */

#ifndef MODULES_TERMINAL_TERMINAL_H_
#define MODULES_TERMINAL_TERMINAL_H_

#include "queue/queue.h"

QueueRecord_t* terminal_rx_queue;
QueueRecord_t* terminal_tx_queue;


void terminal_init(void);
void terminal_RunPeriodic(void);

#endif /* MODULES_TERMINAL_TERMINAL_H_ */
