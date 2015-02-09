/*
 * main.c
 *
 *  Created on: Jan 28, 2015
 *      Author: tgack
 *
 *	 The MIT License (MIT)
 *
 *	Copyright (c) 2015 Timothy Gack
 *
 *	Permission is hereby granted, free of charge, to any person obtaining a copy
 *	of this software and associated documentation files (the "Software"), to deal
 *	in the Software without restriction, including without limitation the rights
 *	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *	copies of the Software, and to permit persons to whom the Software is
 *	furnished to do so, subject to the following conditions:
 *
 *	The above copyright notice and this permission notice shall be included in all
 *	copies or substantial portions of the Software.
 *
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *	SOFTWARE.
 *
 *
 */


#include <stdint.h>
#include "mke04z4.h"
#include "common.h"

#include "mke04z4_watchdog.h"
#include "mke04z4_gpio.h"


static uint32_t loopCounter = 0L;

static void initGPIO(void);

int main(void)
{

	/* Disable interrupts until all the peripherals are initialized. */
	DisableInterrupts;

	/* The watchdog is enabled by default */
	/* The watchdog timer is enabled coming out of reset, */
	/* comment out the next line of code to keep the watchdog */
	/* running. */
	/* Watchdog_Disable(); */

	/* Startup the system tick counter. Setup for a 1mS interrupt period. */
	SysTick_Config(16000);

	/* Initialize GPIO */
	initGPIO();

	/* Enable interrupts  */
	EnableInterrupts;

	for(;;)
	{
		/* Un-comment the following line if the watchdog timer is enabled.  */
		Watchdog_Refresh();
		loopCounter++;
	}
}


static void initGPIO(void)
{
	/* TODO: Put GPIO Initialization here. */


}
