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
#include "hd44780/hd44780.h"

uint8_t test_foo(uint8_t* data,size_t dlen, uint32_t id,void* dptr)
{

	CANt_send_string(0x77,0,"hm");
}
uint8_t test_foo2(uint8_t* data,size_t dlen, uint32_t id,void* dptr)
{
	BlueLED_NegVal();

}

obiektLCD napis1;
obiektLCD napis2;
obiektLCD napis3;
obiektLCD napis4;


void vmain(void) {

	can_inst=CAN1_Init(NULL);

	CANt_init();
	terminal_init();
	hd44780_init();
	hd44780_place_cursor(0,0);
	hd44780_put_string("test init");

	mtimer_t gen_timer;
	mtimer_RegisterTimer(&gen_timer, 1000, 1000);
	mtimer_start(&gen_timer);

	mtimer_t timer_100ms;

	mtimer_RegisterTimer(&timer_100ms, 100, 100);
	mtimer_start(&timer_100ms);

	CANt_RegisterCallback(test_foo,0x44,NULL);
	CANt_RegisterCallback(test_foo2,0x45,NULL);

	for (;;) {

		CANt_RunPeriodic();
		terminal_RunPeriodic();

		if (mtimer_isTimeout(&gen_timer) == 1) {

			mtimer_reload(&gen_timer);
			GreenLED_NegVal();

			CANt_send_string(0x66,0,"hej4");
			CANt_send_string(0x67,0,"hej1");
			CANt_send_string(0x68,0,"hej2");

			static uint8_t cnt=0;
			char buff[10];

			sprintf(buff,"hoho%d",cnt);

			hd44780_write_to_buff(buff,0,1,&napis1);

			sprintf(buff,"test%d",cnt);
			hd44780_write_to_buff(buff,0,0,&napis2);

			sprintf(buff,"cos%d",cnt);
			hd44780_write_to_buff(buff,8,0,&napis3);

			cnt++;


		}

		if (mtimer_isTimeout(&timer_100ms) == 1){

			mtimer_reload(&timer_100ms);

			char buff[10];

			static uint8_t cnt=0;

			sprintf(buff,"inne%d",cnt++);
			hd44780_write_to_buff(buff,8,1,&napis4);

			hd44780_RunPeriodic();
		}


	}

}

