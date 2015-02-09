/*
 * main.c
 *
 *  Created on: Jan 28, 2015
 *      Author: tgack
 */


#include <stdint.h>
#include "mke04z4.h"
#include "common.h"

#include "mke04z4_watchdog.h"


static uint32_t loopCounter = 0L;


int main(void)
{

	/* Disable interrupts until all the peripherals are initialized. */
	DisableInterrupts;

	/* The watchdog is enabled by default */
	/* The watchdog timer is enabled coming out of reset, */
	/* comment out the next line of code to keep the watchdog */
	/* running. */
	Watchdog_Disable();

	/* Startup the system tick counter. Setup for a 1mS interrupt period. */
	SysTick_Config(16000);


	/* Enable interrupts  */
	EnableInterrupts;

	for(;;)
	{
		/* Un-commnent the following line if the watchdog timer is enabled.  */
		/* Watchdog_Refresh(); */


		loopCounter++;
	}
}
