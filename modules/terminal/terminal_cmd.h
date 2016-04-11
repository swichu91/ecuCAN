/*
 * terminal_cmd.h
 *
 *  Created on: 7 kwi 2016
 *      Author: Mateusz
 */

#ifndef MODULES_TERMINAL_TERMINAL_CMD_H_
#define MODULES_TERMINAL_TERMINAL_CMD_H_

#include "shell/shell.h"

uint8_t foo_test(char **arg_tab, uint8_t arg_cnt)
{

}


cmd_entry_t cmd_tab_usart[SHELL_MAX_NR_REGISTERED_COMMANDS]=
{
		{foo_test,NULL,NULL,"test"}
};



#endif /* MODULES_TERMINAL_TERMINAL_CMD_H_ */
