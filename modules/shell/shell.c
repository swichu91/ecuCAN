/*
 * shell.c
 *
 *  Created on: 29 mar 2016
 *      Author: MateuszPiesta
 */

#include "shell.h"
#include "shell_conf.h"
#include <stdint.h>
#include <string.h>

typedef struct _shell {

	void* hist_queue;

	char* line_buff;
	uint32_t line_buff_pos;
	size_t line_buff_size;

	cmd_entry *cmd_etab[SHELL_MAX_NR_REGISTERED_COMMANDS];

	uint8_t (*shell_write)(char* str);
	uint8_t (*shell_read)(char* str_out);
	uint8_t (*shell_cup)(void);
	uint8_t (*shell_cdown)(void);
	uint8_t (*shell_cleft)(void);
	uint8_t (*shell_cright)(void);
	uint8_t (*shell_enter)(void);
	uint8_t (*shell_bs)(void);

} shell_t;

typedef enum
{
	LINE_BUFF_OK =0,
	LINE_BUFF_FULL =1,
}lbuff_e;

void shell_RegisterFunctions(shell_t* shell, uint8_t (*shell_write)(char* str),

		uint8_t (*shell_read)(char* str_out), uint8_t (*shell_cup)(void),
		uint8_t (*shell_cdown)(void), uint8_t (*shell_cleft)(void),
		uint8_t (*shell_cright)(void), uint8_t (*shell_enter)(void),
		uint8_t (*shell_bs)(void)) {
	//assert for each foo pointer

	shell->shell_write = shell_write;
	shell->shell_read = shell_read;
	shell->shell_enter = shell_enter;
	shell->shell_cup = shell_cup;
	shell->shell_cright = shell_cright;
	shell->shell_cleft = shell_cleft;
	shell->shell_cdown = shell_cdown;
	shell->shell_bs = shell_bs;

}

void shell_RegisterCmdTab(shell_t* shell, cmd_entry* cmd_tab, size_t ele) {
	uint8_t i;

	//assert if ele > SHELL_MAX_NR_REGISTERED_COMMANDS

	for (i = 0; i < ele; i++) {

		shell[i].cmd_etab[i] = &cmd_tab[i];

	}
}

uint8_t shell_Init(shell_conf* conf) {

}

static lbuff_e shell_MngtLineBuff(shell_t* shell,char* byte)
{
	if(shell->line_buff_pos > shell->line_buff_size){
		shell->line_buff_pos = 0;
		return LINE_BUFF_FULL;
	}
	else
	{
		shell->line_buff[shell->line_buff_pos] = *byte;
		shell->line_buff_pos++;
		return LINE_BUFF_OK;
	}

}


void shell_RunPeriodic(shell_t* shell) {

	char byte;

	shell->shell_read(&byte);

	if(byte !=NULL)
	{
		if(shell_MngtLineBuff(shell,byte) == LINE_BUFF_OK)
		{
			//TODO: check for new line,bs , arrows /left/right/up/down


		}
		else
		{
			// line buffer full, clear it and then proceed to next line
		}


	}

}
