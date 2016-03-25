/**
 * \file timer_timeout.c
 * \brief
 * \note
 * \author JorgeAlvarez
 * \copyright Impact Clean Power Technology 2015
 * \version Template ICPT-C-Eclipse-Template-v1
 */

/* INCLUDE FILES */

#include "timer_timeout.h"
#include "PE_Types.h"
#include <assert.h>

/* CONFIGURATION */

/* DEFINES */

/* CONSTANTS */

/* DATA TYPES */

static mtimer_t *mtimers_list[MTIMERS_MAX_TIMER_NR] = { NULL };

/* LOCAL VARIABLES */

/* GLOBAL VARIABLES */

/* LOCAL MACROS */

/* LOCAL FUNCTIONS PROTOTYPES */

/* GLOBAL FUNCTIONS */

uint32_t mtimer_getPreset(mtimer_t const * const tt) {

	return tt->Preset;

}

uint32_t mtimer_getTimer(mtimer_t const * const tt) {

	return tt->Timer;

}

uint8_t mtimer_isTimeout(mtimer_t const * const tt) {

	return tt->Timeout;

}

uint8_t mtimer_isActivated(mtimer_t const * const tt) {

	return tt->Activated;

}

uint8_t mtimer_isEnabled(mtimer_t const * const tt) {

	return tt->Enabled;

}

void mtimer_setPreset(mtimer_t * const tt, uint32_t const preset) {

	tt->Preset = preset;

}

void mtimer_reload(mtimer_t * const tt) {

	tt->Timer = tt->Preset;
	tt->Activated = 1u;
	mtimer_start(tt);
	mtimer_reset(tt);

}

/* XXX G.K. CodeReview 102: seems TIMER_TIMEOUT_tick(t) is special case of   TIMER_TIMEOUT_tickTime(t,1) potential to refactoring */
uint8_t mtimer_tick(mtimer_t * const tt) {

	if (tt->Enabled == 0u) {
		/* */
	} else {
		if (tt->Timer > 1u) {
			(tt->Timer)--;
		} else {
			tt->Timer = 0u;
			tt->Timeout = 1u;
		}
	}

	return tt->Timeout;

}

uint8_t mtimer_tickTime(mtimer_t * const tt, uint32_t const tickTime) {

	if (tt->Enabled == 0u) {
		/* */
	} else {
		if (tt->Timer > tickTime) {
			(tt->Timer) -= tickTime;
		} else {
			tt->Timer = 0u;
			tt->Timeout = 1u;
		}
	}

	return tt->Timeout;

}

void mtimer_start(mtimer_t * const tt) {

	tt->Enabled = 1u;

}

void mtimer_stop(mtimer_t * const tt) {

	tt->Enabled = 0u;
	tt->Timer = tt->Preset;

}

void mtimer_reset(mtimer_t * const tt) {

	tt->Timeout = 0u;

}

void mtimer_pause(mtimer_t * const tt) {

	tt->Enabled = 0u;

}

void mtimer_ScanTimers(void) {
	uint8_t i;

	for (i = 0; i < MTIMERS_MAX_TIMER_NR; i++) {
		if (mtimers_list[i] != NULL) {
			mtimer_tick(mtimers_list[i]);
		}
	}

}

void mtimer_RegisterTimer(mtimer_t * const tt, uint32_t const timer,
		uint32_t const preset) {

	assert(tt != NULL);

	uint8_t i;

	for (i = 0; i < MTIMERS_MAX_TIMER_NR; i++) {
		if (mtimers_list[i] == NULL) // first empty lookup
		{
			tt->Activated = 0u;
			tt->Enabled = 0u;
			tt->Timeout = 0u;
			tt->Preset = preset;
			tt->Timer = timer;

			mtimers_list[i] = tt;

			return;

		}
	}

}

/* LOCAL FUNCTIONS */

