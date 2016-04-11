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
#include <stdlib.h>



sherr_t shell_Init(shell_t* shell, size_t linebuf_len) {

	SHELL_ASSERT(shell != NULL);

	memset(shell, 0, sizeof(*shell));

	if ((shell->line_buff = malloc(linebuf_len)) == NULL) {
		return SHELL_ERR_MEM;
	}
	shell->line_buff_size = linebuf_len;

	return SHELL_OK;

}

void shell_RegisterFunctions(shell_t* shell,
		uint8_t (*shell_write)(char* str, size_t len),
		uint8_t (*shell_read)(char* str_out)) {

	SHELL_ASSERT(shell != NULL);
	SHELL_ASSERT(shell_write != NULL);
	SHELL_ASSERT(shell_read != NULL);

	shell->shell_write = shell_write;
	shell->shell_read = shell_read;


}

void shell_RegisterCmdTab(shell_t* shell, cmd_entry_t* cmd_tab, size_t ele) {
	uint8_t i;

	SHELL_ASSERT(shell != NULL);
	SHELL_ASSERT(cmd_tab != NULL);
	SHELL_ASSERT(ele <= SHELL_MAX_NR_REGISTERED_COMMANDS);

	for (i = 0; i < ele; i++) {

		shell->cmd_etab[i] = &cmd_tab[i];

	}
}

sherr_t shell_AppendCmdTab(shell_t* shell, cmd_entry_t* cmd_tab, size_t ele) {

	SHELL_ASSERT(shell !=NULL);
	SHELL_ASSERT(cmd_tab !=NULL);
	uint8_t i = 0;
	sherr_t ret;

	for (i = 0; i < SHELL_MAX_NR_REGISTERED_COMMANDS; i++) {//look for first empty

		if (shell->cmd_etab[i] == NULL)
			break;

	}

	if (i == SHELL_MAX_NR_REGISTERED_COMMANDS)	// cmd_tab full
		ret = SHELL_ERR_TAB_FULL;
	else if ((SHELL_MAX_NR_REGISTERED_COMMANDS - i) >= ele) {
		uint8_t j;

		for (j = 0; j < ele; j++, i++) {

			shell->cmd_etab[i] = &cmd_tab[j];

		}

		ret = SHELL_OK;
	} else { // there is not enough space for append
		ret = SHELL_ERR_SPACE;

	}

	return ret;

}

uint8_t shell_RegisterCodes(shell_t* shell, char *bs_code, char *newline_code,
		char *arrowl_code, char *arrowr_code, char *arrowu_code,
		char *arrowd_code) {


	SHELL_ASSERT(shell != NULL);

	shell->bs_code = bs_code;
	shell->newline_code = newline_code;
	shell->arrowd_code = arrowd_code;
	shell->arrowl_code = arrowl_code;
	shell->arrowr_code = arrowr_code;
	shell->arrowu_code = arrowu_code;

}

typedef enum {
	LINE_BUFF_OK = 0, LINE_BUFF_FULL = 1,
} lbuff_e;

static lbuff_e shell_MngtLineBuff(shell_t* shell, char* byte) {
	if (shell->line_buff_pos > shell->line_buff_size) {
		shell->line_buff_pos = 0;
		memset(shell->line_buff, 0, shell->line_buff_size);	// clear character buffer
		return LINE_BUFF_FULL;
	} else {
		shell->line_buff[shell->line_buff_pos] = *byte;
		shell->line_buff_pos++;
		return LINE_BUFF_OK;
	}

}

void shell_RunPeriodic(shell_t* shell) {

	SHELL_ASSERT(shell != NULL);

	char byte;

	shell->shell_read(&byte);

	if (byte != 0) {
		if (shell_MngtLineBuff(shell, &byte) == LINE_BUFF_OK) {

			if (*shell->newline_code == byte) {
				shell->shell_write(shell->newline_code,
						strlen(shell->newline_code));
				//save current buffer to history queue then
			} else if (*shell->bs_code == byte) {

			} else if (*shell->arrowu_code == byte) {

			} else if (*shell->arrowd_code == byte) {

			} else if (*shell->arrowl_code == byte) {

			} else if (*shell->arrowr_code == byte) {

			} else if ((byte >= 0x20) && (byte <= 0x7E)) // all ascii 'human' characters available from standard keyboard
					{
				shell->shell_write(&byte,1);

			} else // probably first code for arrow
			{

			}

		} else {
			// line buffer full, clear it and then proceed to next line
			shell->shell_write(shell->newline_code,
					strlen(shell->newline_code));
		}

	}

}
