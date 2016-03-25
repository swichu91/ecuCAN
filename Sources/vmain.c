/*
 * vmain.c
 *
 *  Created on: 23 mar 2016
 *      Author: Mateusz
 */

#include "GreenLED.h"
#include "BlueLED.h"
#include "timer_timeout/timer_timeout.h"
#include "CAN1.h"
#include "vmain.h"
#include "can_t/can_t.h"
#include "DbgTerminal.h"
#include "terminal/terminal.h"

uint8_t test_foo(uint8_t* data,size_t dlen, uint32_t id,void* dptr)
{

	CANt_send_string(0x77,0,"hm");
}
uint8_t test_foo2(uint8_t* data,size_t dlen, uint32_t id,void* dptr)
{
	BlueLED_NegVal();

}

void vmain(void) {

	can_inst=CAN1_Init(NULL);

	CANt_init();
	terminal_init();

	mtimer_t gen_timer;
	mtimer_RegisterTimer(&gen_timer, 1000, 1000);
	mtimer_start(&gen_timer);

	CANt_RegisterFoo(test_foo,0x44,NULL);
	CANt_RegisterFoo(test_foo2,0x45,NULL);

	for (;;) {


		CANt_RunPeriodic();
		terminal_RunPeriodic();

		if (mtimer_isTimeout(&gen_timer) == 1) {

			mtimer_reload(&gen_timer);
			GreenLED_NegVal();

			CANt_send_string(0x66,0,"hej4");
			CANt_send_string(0x67,0,"hej1");
			CANt_send_string(0x68,0,"hej2");


		}
	}

}

