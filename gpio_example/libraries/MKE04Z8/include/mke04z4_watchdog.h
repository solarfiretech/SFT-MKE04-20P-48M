/*
 * mke04z4_watchdog.h
 *
 *  Created on: Feb 5, 2015
 *      Author: tgack
 */

#ifndef MKE04_INCLUDE_MKE04Z4_WATCHDOG_H_
#define MKE04_INCLUDE_MKE04Z4_WATCHDOG_H_

typedef struct {
    struct {
	uint16_t    bIntEnable      : 1;    /* watchdog interrupt enable */
	uint16_t    bDisable        : 1;    /* disable watchdog */
	uint16_t    bWaitEnable     : 1;    /* enable watchdog in wait mode */
	uint16_t    bStopEnable     : 1;    /* enable watchdog in stop mode */
	uint16_t    bDbgEnable      : 1;    /* enable watchdog in debug mode */
	uint16_t    bWinEnable      : 1;    /* enable watchdog window mode */
	uint16_t    bUpdateEnable   : 1;    /* enable update of watchdog control */
	uint16_t    bClkSrc         : 2;    /* watchdog clock source selection */
	uint16_t    bPrescaler      : 1;    /* prescaler */
    }sBits;                             /* bitfield structure  */
    uint16_t    u16TimeOut;             /* watchdog timeout value */
    uint16_t    u16WinTime;             /* watchdog window value */
} Watchdog_ConfigType, *Watchdog_ConfigPtr;  /* watchdog configuration structure type */



void Watchdog_Disable(void);
void Watchdog_Refresh(void);
void Watchdog_DisableEnableUpdate(void);
void Watchdog_Enable(void);

#endif /* MKE04_INCLUDE_MKE04Z4_WATCHDOG_H_ */
