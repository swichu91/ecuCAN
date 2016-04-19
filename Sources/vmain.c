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
obiektLCD napis5;
obiektLCD napis6;
obiektLCD napis7;

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

			char buff[10];

			hd44780_write_to_buff(0x01,1,0,0,&napis5);
			sprintf(buff,"2222");
			hd44780_write_to_buff(buff,strlen(buff),1,0,&napis1);

			hd44780_write_to_buff(0x00,1,7,0,&napis6);
			sprintf(buff,"2233");
			hd44780_write_to_buff(buff,strlen(buff),8,0,&napis3);

			sprintf(buff,"353V");
			hd44780_write_to_buff(buff,strlen(buff),13,0,&napis2);

			sprintf(buff,"66%");
			hd44780_write_to_buff(buff,strlen(buff),14,1,&napis4);



		}

		if (mtimer_isTimeout(&timer_100ms) == 1){

			mtimer_reload(&timer_100ms);

			hd44780_RunPeriodic();
		}


	}

}

