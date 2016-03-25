/*
 * can_t.h
 *
 *  Created on: 24 mar 2016
 *      Author: Mateusz
 */

#ifndef MODULES_CAN_T_CAN_T_H_
#define MODULES_CAN_T_CAN_T_H_

#include "queue/queue.h"
#include "CAN1.h"


#define CAN_T_TIMER_VAL	10
#define CAN_T_MAX_NR_REGISTERED_FUNCTIONS	50

typedef struct _foo
{
	void* dptr;
	uint32_t id;
	uint8_t (*do_work)(uint8_t* data,size_t dlen, uint32_t id,void* dptr);
}foo_t;


QueueRecord_t* can_rx_queue;

void CANt_init(void);
void CANt_RunPeriodic(void);
void CANt_send_string(LDD_CAN_TMessageID id,LDD_CAN_TFrameType type,char* s);
void CANt_send(LDD_CAN_TFrame* msg);
void CANt_sendp(LDD_CAN_TMessageID id, LDD_CAN_TFrameType type, uint8_t* data,size_t len) ;
void CANt_RegisterFoo(uint8_t (*foo)(uint8_t* data,size_t dlen, uint32_t id,void* dptr),uint32_t id, void* dptr);
void CANt_ParseFrame(uint8_t* data, size_t dlen, uint32_t id);



#endif /* MODULES_CAN_T_CAN_T_H_ */
