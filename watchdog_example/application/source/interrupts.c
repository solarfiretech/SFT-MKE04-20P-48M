/*
 * interrupts.c
 *
 *  Created on: Feb 8, 2015
 *      Author: tgack
 */

#include "mke04z4.h"

uint64_t systemTickCounter = 0L;

/*
 * Interrupt Service Routine.
 *
 * Handles the system tick interrupt.
 *
 */
void SysTick_Handler(void)
{
	systemTickCounter++;
}


