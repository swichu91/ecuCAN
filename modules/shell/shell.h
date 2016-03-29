/*
 * shell.h
 *
 *  Created on: 29 mar 2016
 *      Author: MateuszPiesta
 */

#ifndef MODULES_SHELL_SHELL_H_
#define MODULES_SHELL_SHELL_H_

#include "shell_conf.h"
#include <stdint.h>

typedef struct _shell_conf
{


}shell_conf;


typedef struct _cmd_entry
{
	uint8_t (*do_cmd)(char **arg_tab, uint8_t arg_cnt);
	char* help_str;
	char* desc;
	char* name;

}cmd_entry;

void foo_test(char **arg_tab, uint8_t arg_cnt)
{

}


cmd_entry cmd_tab[SHELL_MAX_NR_REGISTERED_COMMANDS]=
{
		{foo_test,NULL,NULL,"test"}
};


#endif /* MODULES_SHELL_SHELL_H_ */
