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

typedef enum {
	LINE_BUFF_OK = 0,
	LINE_BUFF_FULL = 1,
	LINE_BUFF_EMPTY = 2,
	LINE_BUFF_REACH_MIN = 3,
	LINE_BUFF_REACH_MAX = 4
} lbuff_e;

typedef enum {
	LINE_BUFF_ADD_CHAR = 0,
	LINE_BUFF_BS = 1,
	LINE_BUFF_CLEAR_WHOLE = 2,
	LINE_BUFF_POS_LEFT = 3,
	LINE_BUFF_POS_RIGHT = 4
} lbuff_action;

/* Forward declarations */
static void shell_send_escape_sequence(shell_t* shell, char* byte);

sherr_t shell_Init(shell_t* shell, size_t linebuf_len) {

	SHELL_ASSERT(shell != NULL);

	memset(shell, 0, sizeof(*shell));

	if ((shell->line_buff = malloc(linebuf_len)) == NULL) {
		return SHELL_ERR_MEM;
	}
	shell->line_buff_size = linebuf_len;
	memset(shell->line_buff, 0, linebuf_len);

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

	for (i = 0; i < SHELL_MAX_NR_REGISTERED_COMMANDS; i++) { //look for first empty

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

uint8_t shell_RegisterCodes(shell_t* const shell, const char *prefix,
		const char *bs_code, const char *newline_code, const char *arrowl_code,
		const char *arrowr_code, const char *arrowu_code,
		const char *arrowd_code) {

	SHELL_ASSERT(shell != NULL);

	shell->line_prefix = (char*) prefix;
	shell->bs_code = (char*) bs_code;
	shell->newline_code = (char*) newline_code;
	shell->arrowd_code = (char*) arrowd_code;
	shell->arrowl_code = (char*) arrowl_code;
	shell->arrowr_code = (char*) arrowr_code;
	shell->arrowu_code = (char*) arrowu_code;

}



static lbuff_e shell_MngtLineBuff(shell_t* shell, char* byte,
		lbuff_action action) {

	switch (action) {

	case LINE_BUFF_ADD_CHAR:
		if (shell->line_buff_pos > shell->line_buff_size) {
			shell->line_buff_pos = 0;
			memset(shell->line_buff, 0, shell->line_buff_size);	// clear character buffer
			shell->line_buff[0] = '\0';
			return LINE_BUFF_FULL;
		} else {
			shell->line_buff[shell->line_buff_pos] = *byte;
			shell->line_buff_pos++;
			if (shell->line_buff_pos == strlen(shell->line_buff)) {
				shell->line_buff[shell->line_buff_pos] = '\0';
			}
			return LINE_BUFF_OK;
		}

		break;

	case LINE_BUFF_BS:
		if (shell->line_buff_pos > 0) {

			shell->line_buff[shell->line_buff_pos - 1] = '\0';
			shell->line_buff_pos--;
			return LINE_BUFF_OK;
		} else {
			return LINE_BUFF_EMPTY;
		}
		break;

	case LINE_BUFF_CLEAR_WHOLE:

		memset(shell->line_buff, 0, shell->line_buff_size);	// clear character buffer
		shell->line_buff[0] = '\0';
		shell->line_buff_pos = 0;
		return LINE_BUFF_OK;

		break;

	case LINE_BUFF_POS_LEFT:

		if (shell->line_buff_pos == 0) {
			return LINE_BUFF_REACH_MIN;
		} else {
			shell->line_buff_pos--;
			shell_send_escape_sequence(shell, shell->arrowl_code);
			return LINE_BUFF_OK;
		}
		break;

	case LINE_BUFF_POS_RIGHT:

		if (shell->line_buff_pos == strlen(shell->line_buff)) {
			return LINE_BUFF_REACH_MAX;
		} else {
			shell->line_buff_pos++;
			shell_send_escape_sequence(shell, shell->arrowr_code);
			return LINE_BUFF_OK;
		}

		break;

	}

}

static void shell_write_newline(shell_t* shell) {
	shell->shell_write(shell->newline_code, strlen(shell->newline_code));
	shell->shell_write(shell->line_prefix, strlen(shell->line_prefix));

}

static void shell_send_escape_sequence(shell_t* shell, char* byte) {

	char buff[3] = { 0 };

	buff[0] = 0x1B;
	buff[1] = '[';
	buff[2] = *byte;
	shell->shell_write(buff, 3);
}

void shell_RunPeriodic(shell_t* shell) {

	SHELL_ASSERT(shell != NULL);

	char byte;
	static char escape_sequence_start = 0;

	shell->shell_read(&byte);

	if (byte != 0) {

		if (byte == 0x1B) // start of escape sequence
				{
			escape_sequence_start = 1;
		} else if ((escape_sequence_start == 1) && (byte == '[')) {
			// omit this byte
		} else if (*shell->newline_code == byte) {
			shell_write_newline(shell);
			shell_MngtLineBuff(shell, NULL, LINE_BUFF_CLEAR_WHOLE);
			//save current buffer to history queue then
		} else if (*shell->bs_code == byte) {

			if (shell_MngtLineBuff(shell, NULL, LINE_BUFF_BS) == LINE_BUFF_OK) {
				shell->shell_write(shell->bs_code, 1);
			}
			else
			{
				// do nothing, there is nothing to clear inside line buff
			}
		} else if ((*shell->arrowu_code == byte)
				&& (escape_sequence_start == 1)) {
			escape_sequence_start = 0;

		} else if ((*shell->arrowd_code == byte)
				&& (escape_sequence_start == 1)) {
			escape_sequence_start = 0;
		} else if ((*shell->arrowl_code == byte)
				&& (escape_sequence_start == 1)) {
			escape_sequence_start = 0;

			shell_MngtLineBuff(shell, NULL, LINE_BUFF_POS_LEFT);

		} else if ((*shell->arrowr_code == byte)
				&& (escape_sequence_start == 1)) {
			escape_sequence_start = 0;

			shell_MngtLineBuff(shell, NULL, LINE_BUFF_POS_RIGHT);

		} else if ((byte >= 0x20) && (byte <= 0x7E)) // all ascii 'human' characters available from standard keyboard
				{
			if (shell_MngtLineBuff(shell, &byte, LINE_BUFF_ADD_CHAR)
					== LINE_BUFF_OK) {
				shell->shell_write(&byte, 1);

			} else {
				// line buffer full, clear it and then proceed to next line
				shell_MngtLineBuff(shell, NULL, LINE_BUFF_CLEAR_WHOLE); // clears line buff
				shell_write_newline(shell);
			}

		}

	}

}
