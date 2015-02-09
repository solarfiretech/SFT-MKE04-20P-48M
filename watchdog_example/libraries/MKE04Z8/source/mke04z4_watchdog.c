/*
 * mke04z4_watchdog.c
 *
 *  Created on: Feb 5, 2015
 *      Author: tgack
 */


#include "mke04z4.h"
#include "common.h"
#include "mke04z4_watchdog.h"




static inline void Watchdog_Unlock();

/*
 * Disables the watchdog timer.
 */
void Watchdog_Disable(void)
{
	uint8_t cs1;
	uint8_t cs2;
	uint16_t toval;
	uint16_t win;

	cs1 = WDOG->CS1 & ~WDOG_CS1_EN_MASK;
	cs2 = WDOG->CS2;
	toval = WDOG->TOVAL;
	win = WDOG->WIN;

	/* Unlock the watchdog */
	Watchdog_Unlock();

	/* Write registers. */
	WDOG->CS2 = cs2;
	WDOG->TOVAL = toval;
	WDOG->WIN = win;
	WDOG->CS1 = cs1;

}

/*
 * Disable watch dog but the watch dog, but allow it to be enabled at
 * a later point in time.
 */
void Watchdog_DisableEnableUpdate(void)
{
	uint8_t cs1;
	uint8_t cs2;
	uint16_t toval;
	uint16_t win;

	cs1 = WDOG->CS1;
	cs2 = WDOG->CS2;
	toval = WDOG->TOVAL;
	win = WDOG->WIN;

	cs1 &= ~WDOG_CS1_EN_MASK;
	cs2 |= WDOG_CS1_UPDATE_MASK;

	/* Unlock the watchdog for register update. */
	Watchdog_Unlock();

	WDOG->CS2 = cs2;
	WDOG->TOVAL = toval;
	WDOG->WIN = win;
	WDOG->CS1 = cs1;


}

/*
 * Watchdog timer enable routine.
 */
void Watchdog_Enable(void)
{
	uint8_t cs1;

	cs1 = WDOG->CS1;

	/* Unlock the watchdog for register update. */
	Watchdog_Unlock();

	WDOG->CS1 = cs1;
}

/*
 * Initialize the watchdog timer from a configuration structure
 */
void Watchdog_Init(Watchdog_ConfigPtr pConfig)
{
    uint8_t     cs1;
    uint8_t     cs2;
    uint16_t    toval;
    uint16_t    win;

    cs1       = 0x80;                                   /* default CS1 register value */
    cs2       = 0;
    toval    = pConfig->u16TimeOut;
    win      = pConfig->u16WinTime;

    if(pConfig->sBits.bDisable)
    {
        cs1 &= ~WDOG_CS1_EN_MASK;
    }
    if(pConfig->sBits.bIntEnable)
    {
        cs1 |= WDOG_CS1_INT_MASK;
    }
    if(pConfig->sBits.bStopEnable)
    {
        cs1 |= WDOG_CS1_STOP_MASK;
    }
    if(pConfig->sBits.bDbgEnable)
    {
        cs1 |= WDOG_CS1_DBG_MASK;
    }
    if(pConfig->sBits.bWaitEnable)
    {
        cs1 |= WDOG_CS1_WAIT_MASK;
    }
    if(pConfig->sBits.bUpdateEnable)
    {
        cs1 |= WDOG_CS1_UPDATE_MASK;
    }
    if(pConfig->sBits.bWinEnable)
    {
        cs2 |= WDOG_CS2_WIN_MASK;
    }
    if(pConfig->sBits.bPrescaler)
    {
        cs2 |= WDOG_CS2_PRES_MASK;
    }
    cs2   |= (pConfig->sBits.bClkSrc & 0x03);

    /* write registers */
    Watchdog_Unlock();              /* unlock watchdog first */
    WDOG->CS2   = cs2;

    WDOG->TOVAL8B.TOVALL  = toval;
    WDOG->TOVAL8B.TOVALH  = toval >> 8;

    WDOG->WIN8B.WINL  = win;
    WDOG->WIN8B.WINH  = win >> 8;

    WDOG->CS1   = cs1;
}



/*
 * Refresh the watchdog timer
 * Must be called periodically.
 */
void Watchdog_Refresh(void)
{
    DisableInterrupts;
    WDOG->CNT = 0x02A6;
    WDOG->CNT = 0x80B4;
    EnableInterrupts;
}


/*
 * Unlocks the watchdog timer registers for writing.
 */
static inline void Watchdog_Unlock()
{
	WDOG->CNT = 0x20C5;
	WDOG->CNT = 0x28D9;
}



