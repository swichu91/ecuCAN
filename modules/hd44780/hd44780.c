/*
 * hd44780.c
 *
 *  Created on: 18 kwi 2016
 *      Author: Mateusz
 */

#include "hd44780/hd44780.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static char row_buff[HD44780_ROWS_NR][HD44780_ROWS_CNT + 1]; // rows buffers


static void hd44780_put_on_LCD(uint8_t row);

void hd44780_write(unsigned char x, unsigned char op) {

	uint8_t busy;

	HD44780_DATA_OUT
	;

	if (x & 0x10)
		HD44780_SET_D4;
	else
		HD44780_CLR_D4;

	if (x & 0x20)
		HD44780_SET_D5;
	else
		HD44780_CLR_D5;

	if (x & 0x40)
		HD44780_SET_D6;
	else
		HD44780_CLR_D6;

	if (x & 0x80)
		HD44780_SET_D7;
	else
		HD44780_CLR_D7;

	HD44780_CLR_E;
	if (op)
		HD44780_SET_RS;
	else
		HD44780_CLR_RS;

	HD44780_CLR_RW;
	asm("nop");
	asm("nop");

	HD44780_SET_E;
	asm("nop");
	asm("nop");
	HD44780_CLR_E;
	asm("nop");
	asm("nop");

	if (x & 0x01)
		HD44780_SET_D4;
	else
		HD44780_CLR_D4;
	if (x & 0x02)
		HD44780_SET_D5;
	else
		HD44780_CLR_D5;
	if (x & 0x04)
		HD44780_SET_D6;
	else
		HD44780_CLR_D6;
	if (x & 0x08)
		HD44780_SET_D7;
	else
		HD44780_CLR_D7;

	asm("nop");
	asm("nop");

	HD44780_SET_E;
	asm("nop");
	asm("nop");
	HD44780_CLR_E;
	asm("nop");
	asm("nop");

	HD44780_DATA_IN
	;

	HD44780_CLR_RS;
	HD44780_SET_RW;
	HD44780_SET_D7;

	do {
		asm("nop");
		asm("nop");

		HD44780_SET_E;
		asm("nop");
		asm("nop");

		busy = HD44780_IF_D7;
		HD44780_CLR_E;
		asm("nop");
		asm("nop");
		HD44780_SET_E;
		asm("nop");
		asm("nop");
		HD44780_CLR_E;

	} while (busy);

}

void hd44780_put_string(char *s) {

	while (*s)
		hd44780_write(*s++, HD44780_DATA);

}

void hd44780_place_cursor(unsigned char x, unsigned char y) {
	hd44780_write((y * 0x40 + x) | 0x80, HD44780_COMM);
}

void hd44780_init(void) {

	//_delay_ms(160);

	HD44780_DATA_OUT
	HD44780_CTRL_OUT;

	HD44780_CLR_E;
	HD44780_CLR_RS;
	HD44780_CLR_RW;
	HD44780_SET_D4;
	HD44780_SET_D5;
	HD44780_CLR_D6;
	HD44780_CLR_D7;

	unsigned char i;

	for (i = 0; i < 3; i++) {
		asm("nop");
		asm("nop");
		HD44780_SET_E;
		asm("nop");
		asm("nop");
		HD44780_CLR_E;
		asm("nop");
		asm("nop");
		//_delay_ms(5);
	}

	HD44780_CLR_D4;
	asm("nop");
	asm("nop");
	HD44780_SET_E;
	asm("nop");
	asm("nop");
	HD44780_CLR_E;
	asm("nop");
	asm("nop");
	//_delay_ms(1);

	hd44780_write(0x28, HD44780_COMM);
	hd44780_write(0x08, HD44780_COMM);
	hd44780_write(0x01, HD44780_COMM);
	hd44780_write(0x06, HD44780_COMM);
	hd44780_write(0x0C, HD44780_COMM);
	//_delay_ms(100);

	hd44780_clear_row_buff(CLEAR_ALL);

	//create custom characters
	hd44780_write(0x40, HD44780_COMM);

	//arrow up
	hd44780_write(0b00100, HD44780_DATA);
	hd44780_write(0b01110, HD44780_DATA);
	hd44780_write(0b10101, HD44780_DATA);
	hd44780_write(0b00100, HD44780_DATA);
	hd44780_write(0b00100, HD44780_DATA);
	hd44780_write(0b00100, HD44780_DATA);
	hd44780_write(0b00100, HD44780_DATA);
	hd44780_write(0b00100, HD44780_DATA);

	//arrow down
	hd44780_write(0b00100, HD44780_DATA);
	hd44780_write(0b00100, HD44780_DATA);
	hd44780_write(0b00100, HD44780_DATA);
	hd44780_write(0b00100, HD44780_DATA);
	hd44780_write(0b00100, HD44780_DATA);
	hd44780_write(0b10101, HD44780_DATA);
	hd44780_write(0b01110, HD44780_DATA);
	hd44780_write(0b00100, HD44780_DATA);

}

void hd44780_clear_row_buff(cleare_t mode) {
	unsigned char i;

	switch (mode) {

	case CLEAR_ROW1:
		memset(row_buff[0], 32, HD44780_ROWS_CNT + 1);
		row_buff[0][HD44780_ROWS_CNT] = '\0';

		break;

	case CLEAR_ROW2:
		memset(row_buff[1], 32, HD44780_ROWS_CNT + 1);
		row_buff[1][HD44780_ROWS_CNT] = '\0';;

		break;

#if HD44780_ROWS_NR > 2

		case CLEAR_ROW3:
		memset(buffer3,32,HD44780_ROWS_CNT+1);
		buffer3[HD44780_ROWS_CNT] = '\0';

		break;
#endif

#if HD44780_ROWS_NR > 3

		case CLEAR_ROW3:
		memset(buffer4,32,HD44780_ROWS_CNT+1);
		buffer4[HD44780_ROWS_CNT] = '\0';

		break;
#endif

	case CLEAR_ALL:

	{
		uint8_t i = 0;

		for (i = 0; i < HD44780_ROWS_NR; i++) {

			memset(row_buff[i], 32, HD44780_ROWS_CNT + 1);
			row_buff[i][HD44780_ROWS_CNT] = '\0';
		}
	}

		break;

	}
}

void hd44780_write_to_buff(char *txt,size_t len, unsigned char Px, unsigned char Py, obiektLCD *obiekt) {

	assert((Px < HD44780_ROWS_CNT) && (Px >=0));
	assert((Py < HD44780_ROWS_NR) && (Py >=0));

	unsigned char j=0;

	for (j = obiekt->X; j < ((obiekt->X) + obiekt->pozkonc); j++)
		row_buff[Py][j] = 32;

	obiekt->X = Px;
	obiekt->Y = Py;


	if((len + Px) > HD44780_ROWS_CNT)
	{
		len = Px - HD44780_ROWS_CNT;
	}

	uint8_t cnt;

	for(cnt=0;cnt< len;cnt++)
	{
		row_buff[Py][Px++] = *txt++;
	}

	obiekt->pozkonc = len;

}

void hd44780_RunPeriodic(void) {

	uint8_t i;

	for (i = 0; i < HD44780_ROWS_NR; i++) {

		hd44780_place_cursor(0, i);
		hd44780_put_on_LCD(i);
	}
}

static void hd44780_put_on_LCD(uint8_t row)
{
	uint8_t i=0;

	for(i=0;i<HD44780_ROWS_CNT;i++)
	{
		hd44780_write(row_buff[row][i],HD44780_DATA);
	}
}
