/*
 *  LED -- simple LED support
 */

#ifndef __LED_h
#define __LED_h

#if defined(STM32H743xx)
/* These settings are for the STM32H743ZI NUCLEO board */

#include "stm32h7xx_hal.h"

extern GPIO_InitTypeDef GPIO_InitStruct;

extern void ledInit();
extern void ledOn();
extern void ledOff();

#else
/* default case is to print */

#define __LED_PRINTING 1
#define LED_ON()  fputs( "LED ON\n", stderr )
#define LED_OFF() fputs( "LED OFF\n", stderr )
#endif

#ifndef LED_INIT
#define LED_INIT() 
#endif

#endif
