/**
 * \file timer_timeout.h
 * \brief 
 * \note 
 * \author JorgeAlvarez
 * \copyright Impact Clean Power Technology 2015
 * \version Template ICPT-H-Eclipse-Template-v1
 */

#ifndef TIMER_TIMEOUT_H_
#define TIMER_TIMEOUT_H_

/* INCLUDE FILES */

#include "stdint.h"

/* CPP GUARD BEGIN */

#ifdef __cplusplus
extern "C" {
#endif

/* DATA TYPES */

typedef struct {
	uint32_t Timer; /* Current time left to timeout */
	uint32_t Preset; /* Reload value */
	uint8_t Timeout; /* Ever expired? */
	uint8_t Activated; /* Ever activated? */
	uint8_t Enabled; /* Currently enabled? */
	uint8_t prio;
} mtimer_t;

/* EXTERNS */

/* DEFINES */
#define MTIMERS_MAX_TIMER_NR	20

/* MACROS */

/* FUNCTION PROTOTYPES */

uint32_t mtimer_getPreset(mtimer_t const * const tt);

uint32_t mtimer_getTimer(mtimer_t const * const tt);

uint8_t mtimer_isTimeout(mtimer_t const * const tt);

uint8_t mtimer_isActivated(mtimer_t const * const tt);

uint8_t mtimer_isEnabled(mtimer_t const * const tt);

/**
 * TIMER_TIMEOUT_setPreset sets the preset value of the timer.
 * @param tt, TIMER_TIMEOUT structure.
 * @param preset, uint32_t parameter containing the preset value.
 */
void mtimer_setPreset(mtimer_t * const tt, uint32_t const preset);

/**
 * TIMER_TIMEOUT_reload reloads the timer with preset value.
 * @param tt, TIMER_TIMEOUT structure.
 */
void mtimer_reload(mtimer_t * const tt);

/**
 * TIMER_TIMEOUT_tick ticks the timer by one unit of time.
 * @param tt, TIMER_TIMEOUT structure.
 * @return uint8_t Timeout parameter.
 */
uint8_t mtimer_tick(mtimer_t * const tt);

/**
 * TIMER_TIMEOUT_tickTime ticks the timer by a specific unit of time.
 * @param tt, TIMER_TIMEOUT structure.
 * @param tickTime, uint32_t parameter with the tick time of the timer.
 * @return uint8_t Timeout parameter.
 */
uint8_t mtimer_tickTime(mtimer_t * const tt, uint32_t const tickTime);

/**
 * TIMER_TIMEOUT_start starts the timer.
 * @param tt, TIMER_TIMEOUT structure.
 */
void mtimer_start(mtimer_t * const tt);

/**
 * TIMER_TIMEOUT_stop stops the timer and assigns the preset value to the timer.
 * @param tt, TIMER_TIMEOUT structure.
 */
void mtimer_stop(mtimer_t * const tt);

/**
 * TIMER_TIMEOUT_reset resets the timer.
 * @param tt, TIMER_TIMEOUT structure.
 */
void mtimer_reset(mtimer_t * const tt);

/**
 * TIMER_TIMEOUT_pause pauses the timer.
 * @param tt, TIMER_TIMEOUT structure.
 */
void mtimer_pause(mtimer_t * const tt);

void mtimer_ScanTimers(void);
void mtimer_RegisterTimer(mtimer_t * const tt, uint32_t const timer,
		uint32_t const preset);

/* CPP GUARD END */

#ifdef __cplusplus
}
#endif

#endif /* TIMER_TIMEOUT_H_ */

