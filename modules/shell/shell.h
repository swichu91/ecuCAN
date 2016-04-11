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
#include <stddef.h>
#include <assert.h>


#define SHELL_ASSERT(X)	assert(X)

typedef struct _cmd_entry
{
	uint8_t (*do_cmd)(char **arg_tab, uint8_t arg_cnt);
	char* help_str;
	char* desc;
	char* name;

}cmd_entry_t;

typedef struct _shell {

	void* hist_queue;

	char* line_buff;
	uint32_t line_buff_pos;
	size_t line_buff_size;

	cmd_entry_t *cmd_etab[SHELL_MAX_NR_REGISTERED_COMMANDS];

	uint8_t (*shell_write)(char* str, size_t len);
	uint8_t (*shell_read)(char* str);

	char *bs_code;
	char *newline_code;
	char *arrowl_code;
	char *arrowr_code;
	char *arrowu_code;
	char *arrowd_code;

} shell_t;



typedef enum{
	SHELL_OK=0,
	SHELL_ERR_GEN=1,
	SHELL_ERR_TAB_FULL=2,
	SHELL_ERR_SPACE=3,
	SHELL_ERR_MEM=4,

}sherr_t;


sherr_t shell_Init(shell_t* shell, size_t linebuf_len);

void shell_RegisterFunctions(shell_t* shell,
		uint8_t (*shell_write)(char* str, size_t len),
		uint8_t (*shell_read)(char* str_out));

void shell_RegisterCmdTab(shell_t* shell, cmd_entry_t* cmd_tab, size_t ele);

sherr_t shell_AppendCmdTab(shell_t* shell, cmd_entry_t* cmd_tab, size_t ele);

uint8_t shell_RegisterCodes(shell_t* shell, char *bs_code, char *newline_code,
		char *arrowl_code, char *arrowr_code, char *arrowu_code,
		char *arrowd_code);

void shell_RunPeriodic(shell_t* shell);





#endif /* MODULES_SHELL_SHELL_H_ */
