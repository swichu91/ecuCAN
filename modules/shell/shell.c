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




typedef struct _shell
{
	void* hist_queue;

	cmd_entry *cmd_etab[SHELL_MAX_NR_REGISTERED_COMMANDS];
	uint8_t (*shell_write)(char* str,uint8_t fontcolor,uint8_t bgcolor);

}shell_t;

