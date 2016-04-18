/*
 * hd44780.c
 *
 *  Created on: 18 kwi 2016
 *      Author: Mateusz
 */

#include "hd44780/hd44780.h"
#include <stdint.h>

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

	bCLR(all);
}

void bCLR(unsigned char mode) {
	unsigned char i;

	switch (mode) {
	case 1: {

		for (i = 0; i <= 16; i++) {
			buffer1[i] = 32;
		}
		buffer1[16] = 0;

	}
		break;
	case 2: {
		for (i = 0; i <= 16; i++) {
			buffer2[i] = 32;

		}
		buffer2[16] = 0;
	}
		break;
	case 3: {
		for (i = 0; i <= 16; i++) {
			buffer1[i] = 32;
			buffer2[i] = 32;
		}
		buffer1[16] = 0;
		buffer2[16] = 0;

	}
		break;

	}
}

void bRAM(char *txt, unsigned char Px, unsigned char Py, obiektLCD *obiekt) {

	unsigned char i, j;

	if (obiekt->Y == 1) {
		for (j = obiekt->X; j < ((obiekt->X) + obiekt->pozkonc); j++)
			buffer1[j] = 32;

	}
	if (obiekt->Y == 2) {
		for (j = obiekt->X; j < ((obiekt->X) + obiekt->pozkonc); j++)
			buffer2[j] = 32;
	}

	obiekt->X = Px;
	obiekt->Y = Py;

	while (*txt && (Px <= 16)) {
		if (Py == 1) {
			buffer1[Px++] = *txt++;
			i++;

		}
		if (Py == 2) {
			buffer2[Px++] = *txt++;
			i++;

		}
	}

	obiekt->pozkonc = i;

}

void hd44780_RunPeriodic(void) {

	hd44780_place_cursor(0, 0);
	hd44780_put_string(buffer1);
	hd44780_place_cursor(0, 1);
	hd44780_put_string(buffer2);

}

