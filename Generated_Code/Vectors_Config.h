/** ###################################################################
**      Filename    : Vectors_Config.h
**      Processor   : MKE06Z128VLK4
**      Version     : 1.00
** 
**     Copyright : 1997 - 2015 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file Vectors_Config.h                                                  
** @version 01.00
*/         
/*!
**  @addtogroup Vectors_Config_module Vectors_Config module documentation
**  @{
*/         

#ifndef __Vectors_Config_H
#define __Vectors_Config_H

/* MODULE Vectors_Config.h */
  
#include "Cpu.h"
#include "Pins1.h"
#include "GreenLED.h"
#include "BitIoLdd1.h"
#include "TU1.h"
#include "CAN1.h"
#include "BlueLED.h"
#include "BitIoLdd2.h"
#include "DbgTerminal.h"
#include "Inhr1.h"
#include "ASerialLdd1.h"
#include "Events.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PEX_VECTOR_TABLE                                   0x01U     /* Vector table is managed by PEx */ 

/* Vector                 Address                                  No.  Pri  Name                          Description */
#define VECTOR_SP_MAIN    &__SP_INIT                            /* 0x00 -    ivINT_Initial_Stack_Pointer   used by PE */
#define VECTOR_1          (tIsrFunc)&__thumb_startup            /* 0x01 -    ivINT_Initial_Program_Counter used by PE */
#define VECTOR_2          (tIsrFunc)&Cpu_INT_NMIInterrupt       /* 0x02 -2   ivINT_NMI                     used by PE */
#define VECTOR_3          (tIsrFunc)&Cpu_INT_Hard_FaultInterrupt /* 0x03 -1  ivINT_Hard_Fault              used by PE */
#define VECTOR_4          (tIsrFunc)&Unhandled_ivINT_Reserved4  /* 0x04 -    ivINT_Reserved4               unused by PE */
#define VECTOR_5          (tIsrFunc)&Unhandled_ivINT_Reserved5  /* 0x05 -    ivINT_Reserved5               unused by PE */
#define VECTOR_6          (tIsrFunc)&Unhandled_ivINT_Reserved6  /* 0x06 -    ivINT_Reserved6               unused by PE */
#define VECTOR_7          (tIsrFunc)&Unhandled_ivINT_Reserved7  /* 0x07 -    ivINT_Reserved7               unused by PE */
#define VECTOR_8          (tIsrFunc)&Unhandled_ivINT_Reserved8  /* 0x08 -    ivINT_Reserved8               unused by PE */
#define VECTOR_9          (tIsrFunc)&Unhandled_ivINT_Reserved9  /* 0x09 -    ivINT_Reserved9               unused by PE */
#define VECTOR_10         (tIsrFunc)&Unhandled_ivINT_Reserved10 /* 0x0A -    ivINT_Reserved10              unused by PE */
#define VECTOR_11         (tIsrFunc)&Cpu_INT_SVCallInterrupt    /* 0x0B 0    ivINT_SVCall                  used by PE */
#define VECTOR_12         (tIsrFunc)&Unhandled_ivINT_Reserved12 /* 0x0C -    ivINT_Reserved12              unused by PE */
#define VECTOR_13         (tIsrFunc)&Unhandled_ivINT_Reserved13 /* 0x0D -    ivINT_Reserved13              unused by PE */
#define VECTOR_14         (tIsrFunc)&Cpu_INT_PendableSrvReqInterrupt /* 0x0E 0 ivINT_PendableSrvReq        used by PE */
#define VECTOR_15         (tIsrFunc)&TU1_Interrupt              /* 0x0F 64   ivINT_SysTick                 used by PE */
#define VECTOR_16         (tIsrFunc)&Unhandled_ivINT_Reserved16 /* 0x10 -    ivINT_Reserved16              unused by PE */
#define VECTOR_17         (tIsrFunc)&Unhandled_ivINT_Reserved17 /* 0x11 -    ivINT_Reserved17              unused by PE */
#define VECTOR_18         (tIsrFunc)&Unhandled_ivINT_Reserved18 /* 0x12 -    ivINT_Reserved18              unused by PE */
#define VECTOR_19         (tIsrFunc)&Unhandled_ivINT_Reserved19 /* 0x13 -    ivINT_Reserved19              unused by PE */
#define VECTOR_20         (tIsrFunc)&Unhandled_ivINT_Reserved20 /* 0x14 -    ivINT_Reserved20              unused by PE */
#define VECTOR_21         (tIsrFunc)&Unhandled_ivINT_FTMRE      /* 0x15 -    ivINT_FTMRE                   unused by PE */
#define VECTOR_22         (tIsrFunc)&Unhandled_ivINT_LVD_LLW    /* 0x16 -    ivINT_LVD_LLW                 unused by PE */
#define VECTOR_23         (tIsrFunc)&Unhandled_ivINT_IRQ        /* 0x17 -    ivINT_IRQ                     unused by PE */
#define VECTOR_24         (tIsrFunc)&Unhandled_ivINT_I2C0       /* 0x18 -    ivINT_I2C0                    unused by PE */
#define VECTOR_25         (tIsrFunc)&Unhandled_ivINT_I2C1       /* 0x19 -    ivINT_I2C1                    unused by PE */
#define VECTOR_26         (tIsrFunc)&Unhandled_ivINT_SPI0       /* 0x1A -    ivINT_SPI0                    unused by PE */
#define VECTOR_27         (tIsrFunc)&Unhandled_ivINT_SPI1       /* 0x1B -    ivINT_SPI1                    unused by PE */
#define VECTOR_28         (tIsrFunc)&Unhandled_ivINT_UART0      /* 0x1C -    ivINT_UART0                   unused by PE */
#define VECTOR_29         (tIsrFunc)&Unhandled_ivINT_UART1      /* 0x1D -    ivINT_UART1                   unused by PE */
#define VECTOR_30         (tIsrFunc)&ASerialLdd1_Interrupt      /* 0x1E 64   ivINT_UART2                   used by PE */
#define VECTOR_31         (tIsrFunc)&Unhandled_ivINT_ADC0       /* 0x1F -    ivINT_ADC0                    unused by PE */
#define VECTOR_32         (tIsrFunc)&Unhandled_ivINT_ACMP0      /* 0x20 -    ivINT_ACMP0                   unused by PE */
#define VECTOR_33         (tIsrFunc)&Unhandled_ivINT_FTM0       /* 0x21 -    ivINT_FTM0                    unused by PE */
#define VECTOR_34         (tIsrFunc)&Unhandled_ivINT_FTM1       /* 0x22 -    ivINT_FTM1                    unused by PE */
#define VECTOR_35         (tIsrFunc)&Unhandled_ivINT_FTM2       /* 0x23 -    ivINT_FTM2                    unused by PE */
#define VECTOR_36         (tIsrFunc)&Unhandled_ivINT_RTC        /* 0x24 -    ivINT_RTC                     unused by PE */
#define VECTOR_37         (tIsrFunc)&Unhandled_ivINT_ACMP1      /* 0x25 -    ivINT_ACMP1                   unused by PE */
#define VECTOR_38         (tIsrFunc)&Unhandled_ivINT_PIT_CH0    /* 0x26 -    ivINT_PIT_CH0                 unused by PE */
#define VECTOR_39         (tIsrFunc)&Unhandled_ivINT_PIT_CH1    /* 0x27 -    ivINT_PIT_CH1                 unused by PE */
#define VECTOR_40         (tIsrFunc)&Unhandled_ivINT_KBI0       /* 0x28 -    ivINT_KBI0                    unused by PE */
#define VECTOR_41         (tIsrFunc)&Unhandled_ivINT_KBI1       /* 0x29 -    ivINT_KBI1                    unused by PE */
#define VECTOR_42         (tIsrFunc)&Unhandled_ivINT_Reserved42 /* 0x2A -    ivINT_Reserved42              unused by PE */
#define VECTOR_43         (tIsrFunc)&Unhandled_ivINT_ICS        /* 0x2B -    ivINT_ICS                     unused by PE */
#define VECTOR_44         (tIsrFunc)&Unhandled_ivINT_WDOG_EWM   /* 0x2C -    ivINT_WDOG_EWM                unused by PE */
#define VECTOR_45         (tIsrFunc)&Unhandled_ivINT_PWT        /* 0x2D -    ivINT_PWT                     unused by PE */
#define VECTOR_46         (tIsrFunc)&CAN1_RxInterrupt           /* 0x2E 64   ivINT_MSCAN_RX                used by PE */
#define VECTOR_47         (tIsrFunc)&CAN1_TxInterrupt           /* 0x2F 64   ivINT_MSCAN_TX                used by PE */
  
#ifdef __cplusplus
}
#endif

/* END Vectors_Config.h */

#endif /* __Vectors_Config_H */

/*!
** @}
*/
/*
** ###################################################################
**
**     This file is a part of Processor Expert static initialization
**     library for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
