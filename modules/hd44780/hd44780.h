/*
 * hd44780.h
 *
 *  Created on: 18 kwi 2016
 *      Author: Mateusz
 */

#ifndef MODULES_HD44780_HD44780_H_
#define MODULES_HD44780_HD44780_H_

#include "Data_4.h"
#include "Data_5.h"
#include "Data_6.h"
#include "Data_7.h"
#include "Enable.h"
#include "R_W.h"
#include "Reg_sel.h"

#define HD44780_ROWS_CNT	16
#define HD44780_ROWS_NR	2

#define HD44780_SET_D7 Data_7_SetVal()		// 4 bit LCD, makra poszczególnych kana³ów danych
#define HD44780_CLR_D7 Data_7_ClrVal()
#define HD44780_IN_D7  Data_7_SetDir(FALSE)
#define HD44780_IF_D7  Data_7_GetVal()
#define HD44780_OUT_D7 Data_7_SetDir(TRUE)

#define HD44780_SET_D6 Data_6_SetVal()
#define HD44780_CLR_D6 Data_6_ClrVal()
#define HD44780_IN_D6  Data_6_SetDir(FALSE)
#define HD44780_OUT_D6 Data_6_SetDir(TRUE)

#define HD44780_SET_D5 Data_5_SetVal()
#define HD44780_CLR_D5 Data_5_ClrVal()
#define HD44780_IN_D5  Data_5_SetDir(FALSE)
#define HD44780_OUT_D5 Data_5_SetDir(TRUE)

#define HD44780_SET_D4 Data_4_SetVal()
#define HD44780_CLR_D4 Data_4_ClrVal()
#define HD44780_IN_D4  Data_4_SetDir(FALSE)
#define HD44780_OUT_D4 Data_4_SetDir(TRUE)

#define HD44780_OUT_E
#define HD44780_SET_E Enable_SetVal()				// RS,RW,E W takiej kolejnosci leca kable w HD44780
#define HD44780_CLR_E Enable_ClrVal()

#define HD44780_OUT_RW
#define HD44780_SET_RW R_W_SetVal()
#define HD44780_CLR_RW R_W_ClrVal()

#define HD44780_OUT_RS
#define HD44780_SET_RS Reg_sel_SetVal()
#define HD44780_CLR_RS Reg_sel_ClrVal()

#define HD44780_DATA_IN	{HD44780_IN_D4;HD44780_IN_D5;HD44780_IN_D6;HD44780_IN_D7;}
#define HD44780_DATA_OUT {HD44780_OUT_D4;HD44780_OUT_D5;HD44780_OUT_D6;HD44780_OUT_D7;}
#define HD44780_CTRL_OUT {HD44780_OUT_E;HD44780_OUT_RW;HD44780_OUT_RS;}

#define HD44780_COMM 0
#define HD44780_DATA 1

#define freeze 0		// obsluga LCD bez czyszczenia
#define clr 1			// obsluga LCD z czyszczeniem
#define all 3

typedef enum
{
	CLEAR_OFF =0,
	CLEAR_ROW1 = 1,
	CLEAR_ROW2 =2,
	CLEAR_ROW3 =3,
	CLEAR_ROW4 =4,
	CLEAR_ALL =5
}cleare_t;



volatile unsigned char LCD_refresh, tick; 			// flaga do odswiezania LCD

typedef struct								// struktura zapisuj¹ca wspolrzedne
{													//	obiektów w bufferze LCD
	unsigned char X, Y, pozkonc;

} obiektLCD;


void hd44780_RunPeriodic(void);
void hd44780_init(void);
void hd44780_clear_row_buff(cleare_t mode);
void hd44780_write_to_buff(char *txt, unsigned char Px, unsigned char Py, obiektLCD *obiekt);

#endif /* MODULES_HD44780_HD44780_H_ */
