/*
 * can_t.c
 *
 *  Created on: 24 mar 2016
 *      Author: Mateusz
 */
#include "can_t.h"
#include "PE_Types.h"
#include <string.h>
#include "CAN1.h"
#include "queue/queue.h"
#include "timer_timeout/timer_timeout.h"
#include "vmain.h"
#include "BlueLED.h"

QueueRecord_t* can_rx_queue;
static QueueRecord_t* can_tx_queue;
static foo_t function_list[CAN_T_MAX_NR_REGISTERED_FUNCTIONS];

mtimer_t cant_timer;

void CANt_send_string(LDD_CAN_TMessageID id, LDD_CAN_TFrameType type, char* s);
void CANt_ParseFrame(uint8_t* data, size_t dlen, uint32_t id);

void CANt_init(void) {
	can_rx_queue = queue_init(CAN_T_RX_QUEUE_SIZE, sizeof(LDD_CAN_TFrame));
	can_tx_queue = queue_init(CAN_T_TX_QUEUE_SIZE, sizeof(LDD_CAN_TFrame));

	uint8_t i;

	for (i = 0; i < CAN_T_MAX_NR_REGISTERED_FUNCTIONS; i++) {
		function_list[i].do_work = NULL;
		function_list[i].id = 0xFFFF;
		function_list[i].dptr = NULL;

	}

	mtimer_RegisterTimer(&cant_timer, CAN_T_TIMER_VAL, CAN_T_TIMER_VAL);
	mtimer_start(&cant_timer);
}

void CANt_RunPeriodic(void) {
	LDD_CAN_TFrame msg_rx;
	LDD_CAN_TFrame msg_tx;

	if (mtimer_isTimeout(&cant_timer) == 1) {

		mtimer_reload(&cant_timer);

		if (queue_front_and_dequeue(can_rx_queue, &msg_rx) == QERR_OK) {

			CANt_ParseFrame(msg_rx.Data, msg_rx.Length, msg_rx.MessageID);
		}

		if (queue_front_and_dequeue(can_tx_queue, &msg_tx) == QERR_OK) {
			CAN1_SendFrame(can_inst, 1, &msg_tx);
		}

	}

}

void CANt_ParseFrame(uint8_t* data, size_t dlen, uint32_t id) {

	uint8_t i;

	for (i = 0; i < CAN_T_MAX_NR_REGISTERED_FUNCTIONS; i++) // first match lookup
			{

		if (function_list[i].id == id) {
			function_list[i].do_work(data, dlen, id, function_list[i].dptr);
		}
	}

}

void CANt_RegisterCallback(
		uint8_t (*foo)(uint8_t* data, size_t dlen, uint32_t id, void* dptr),
		uint32_t id, void* dptr) {
	uint8_t i;

	for (i = 0; i < CAN_T_MAX_NR_REGISTERED_FUNCTIONS; i++) // first free lookup
			{
		if ((function_list[i].do_work == NULL)
				&& (function_list[i].id == 0xFFFF)) {

			function_list[i].dptr = dptr;
			function_list[i].id = id;
			function_list[i].do_work = foo;
			return;
		}
	}
}

void CANt_send_string(LDD_CAN_TMessageID id, LDD_CAN_TFrameType type, char* s) {

	LDD_CAN_TFrame msg = { 0 };
	uint8_t len = strlen(s);

	if (len > 8) {
		len = 8;
	}

	msg.Data = s;
	msg.MessageID = id;
	msg.FrameType = type;
	msg.Length = len;

	queue_enqueue(can_tx_queue, &msg);
}

void CANt_sendp(LDD_CAN_TMessageID id, LDD_CAN_TFrameType type, uint8_t* data,
		size_t len) {

	LDD_CAN_TFrame msg = { 0 };

	msg.Data = data;
	msg.MessageID = id;
	msg.FrameType = type;
	msg.Length = len;

	queue_enqueue(can_tx_queue, &msg);
}

void CANt_send(LDD_CAN_TFrame* msg) {

	queue_enqueue(can_tx_queue, &msg);
}

