/* ###################################################################
 **     Filename    : Events.c
 **     Project     : CAN_FreeRTOS
 **     Processor   : MKE06Z128VLK4
 **     Component   : Events
 **     Version     : Driver 01.00
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2016-03-23, 23:33, # CodeGen: 0
 **     Abstract    :
 **         This is user's event module.
 **         Put your event handler code here.
 **     Contents    :
 **         Cpu_OnNMI - void Cpu_OnNMI(void);
 **
 ** ###################################################################*/
/*!
 ** @file Events.c
 ** @version 01.00
 ** @brief
 **         This is user's event module.
 **         Put your event handler code here.
 */
/*!
 **  @addtogroup Events_module Events module documentation
 **  @{
 */
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"
#include "Init_Config.h"
#include "PDD_Includes.h"

#ifdef __cplusplus
extern "C" {
#endif 

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "timer_timeout/timer_timeout.h"
#include "can_t/can_t.h"
#include "vmain.h"
#include "queue/queue.h"
#include "terminal/terminal.h"
/*
 ** ===================================================================
 **     Event       :  Cpu_OnNMI (module Events)
 **
 **     Component   :  Cpu [MKE06Z128LK4]
 */
/*!
 **     @brief
 **         This event is called when the Non maskable interrupt had
 **         occurred. This event is automatically enabled when the [NMI
 **         interrupt] property is set to 'Enabled'.
 */
/* ===================================================================*/
void Cpu_OnNMI(void) {
	/* Write your code here ... */
}

/*
 ** ===================================================================
 **     Event       :  Cpu_OnHardFault (module Events)
 **
 **     Component   :  Cpu [MKE06Z128LK4]
 */
/*!
 **     @brief
 **         This event is called when the Hard Fault exception had
 **         occurred. This event is automatically enabled when the [Hard
 **         Fault] property is set to 'Enabled'.
 */
/* ===================================================================*/
void Cpu_OnHardFault(void) {
	/* Write your code here ... */
}

/*
 ** ===================================================================
 **     Event       :  Cpu_OnPendableService (module Events)
 **
 **     Component   :  Cpu [MKE06Z128LK4]
 */
/*!
 **     @brief
 **         This event is called when the Pendable Service exception had
 **         occurred. This event is automatically enabled when the
 **         [Pendable Service] property is set to 'Enabled'.
 */
/* ===================================================================*/
void Cpu_OnPendableService(void) {
	/* Write your code here ... */
}

/*
 ** ===================================================================
 **     Event       :  Cpu_OnSupervisorCall (module Events)
 **
 **     Component   :  Cpu [MKE06Z128LK4]
 */
/*!
 **     @brief
 **         This event is called when the Supervisor Call exception had
 **         occurred. This event is automatically enabled when the
 **         [Supervisor Call] property is set to 'Enabled'.
 */
/* ===================================================================*/
void Cpu_OnSupervisorCall(void) {
	/* Write your code here ... */
}

/*
 ** ===================================================================
 **     Event       :  TU1_OnCounterRestart (module Events)
 **
 **     Component   :  TU1 [TimerUnit_LDD]
 */
/*!
 **     @brief
 **         Called if counter overflow/underflow or counter is
 **         reinitialized by modulo or compare register matching.
 **         OnCounterRestart event and Timer unit must be enabled. See
 **         [SetEventMask] and [GetEventMask] methods. This event is
 **         available only if a [Interrupt] is enabled.
 **     @param
 **         UserDataPtr     - Pointer to the user or
 **                           RTOS specific data. The pointer passed as
 **                           the parameter of Init method.
 */
/* ===================================================================*/
void TU1_OnCounterRestart(LDD_TUserData *UserDataPtr) {
	mtimer_ScanTimers();
	/* Write your code here ... */
}

/*
 ** ===================================================================
 **     Event       :  CAN1_OnFreeTxBuffer (module Events)
 **
 **     Component   :  CAN1 [CAN_LDD]
 */
/*!
 **     @brief
 **         This event is called when the buffer is empty after a
 **         successful transmit of a message. This event is available
 **         only if method SendFrame is enabled.
 **     @param
 **         UserDataPtr     - Pointer to the user or
 **                           RTOS specific data. This pointer is passed
 **                           as the parameter of Init method.
 **     @param
 **         BufferIdx       - Receive message buffer index.
 */
/* ===================================================================*/
void CAN1_OnFreeTxBuffer(LDD_TUserData *UserDataPtr, LDD_CAN_TMBIndex BufferIdx) {
	/* Write your code here ... */
}

/*
 ** ===================================================================
 **     Event       :  CAN1_OnFullRxBuffer (module Events)
 **
 **     Component   :  CAN1 [CAN_LDD]
 */
/*!
 **     @brief
 **         This event is called when the buffer is full after a
 **         successful receive a message. This event is available only
 **         if method ReadFrame or SetRxBufferState is enabled.
 **     @param
 **         UserDataPtr     - Pointer to the user or
 **                           RTOS specific data. This pointer is passed
 **                           as the parameter of Init method.
 **     @param
 **         BufferIdx       - Transmit buffer index.
 */
/* ===================================================================*/
void CAN1_OnFullRxBuffer(LDD_TUserData *UserDataPtr, LDD_CAN_TMBIndex BufferIdx) {
	/* Write your code here ... */
	LDD_CAN_TFrame msg;
	uint8_t buff[8];
	msg.Data = buff;

	CAN1_ReadFrame(can_inst, 0, &msg);

	queue_enqueue(can_rx_queue, &msg);

}

/*
 ** ===================================================================
 **     Event       :  Inhr1_OnRxChar (module Events)
 **
 **     Component   :  Inhr1 [AsynchroSerial]
 **     Description :
 **         This event is called after a correct character is received.
 **         The event is available only when the <Interrupt
 **         service/event> property is enabled and either the <Receiver>
 **         property is enabled or the <SCI output mode> property (if
 **         supported) is set to Single-wire mode.
 **     Parameters  : None
 **     Returns     : Nothing
 ** ===================================================================
 */
void Inhr1_OnRxChar(void) {
	/* Write your code here ... */
	char byte;
	DbgTerminal_ReadChar(&byte);

	queue_enqueue(terminal_rx_queue, &byte);

}

/*
 ** ===================================================================
 **     Event       :  Inhr1_OnTxChar (module Events)
 **
 **     Component   :  Inhr1 [AsynchroSerial]
 **     Description :
 **         This event is called after a character is transmitted.
 **     Parameters  : None
 **     Returns     : Nothing
 ** ===================================================================
 */
void Inhr1_OnTxChar(void) {
	/* Write your code here ... */
}

/*
 ** ===================================================================
 **     Event       :  Inhr1_OnTxComplete (module Events)
 **
 **     Component   :  Inhr1 [AsynchroSerial]
 **     Description :
 **         This event indicates that the transmitter is finished
 **         transmitting all data, preamble, and break characters and is
 **         idle. It can be used to determine when it is safe to switch
 **         a line driver (e.g. in RS-485 applications).
 **         The event is available only when both <Interrupt
 **         service/event> and <Transmitter> properties are enabled.
 **     Parameters  : None
 **     Returns     : Nothing
 ** ===================================================================
 */
void Inhr1_OnTxComplete(void) {
	/* Write your code here ... */
	char dummy;
}

/* END Events */

#ifdef __cplusplus
} /* extern "C" */
#endif 

/*!
 ** @}
 */
/*
 ** ###################################################################
 **
 **     This file was created by Processor Expert 10.5 [05.21]
 **     for the Freescale Kinetis series of microcontrollers.
 **
 ** ###################################################################
 */
