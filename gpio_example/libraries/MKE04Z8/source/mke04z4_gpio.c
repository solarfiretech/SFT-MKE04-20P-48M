/*
 * mke04z4_gpio.c
 *
 *  Created on: Feb 8, 2015
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
 */


#include <stdint.h>
#include "mke04z4.h"


#include "mke04z4_gpio.h"

#define CPU_KE04

/*
 * Initialize the GPIO registers to their default (reset) values
 */
void GPIO_DeInit(GPIO_Type *pGPIO)
{
	if(pGPIO == GPIOA)
	{
		pGPIO->PCOR = 0x00000000;   /* Port Clear Output Register */
		pGPIO->PDDR = 0x00000000;   /* Port Data Direction */
		pGPIO->PDOR = 0x00000000;   /* Port Data Output Register */
		pGPIO->PIDR = 0xFFFFFFFF;   /* Port Input Disable Register */
		pGPIO->PSOR = 0x00000000;   /* Port Set Output Register */
		pGPIO->PTOR = 0x00000000;   /* Port Toggle Output Register */
	}
}

/*
 * GPIO_Init
 * 
 * 		pGPIO 		Pointer to GPIO module, can be GPIOA (MKE04)
 * 		pinMask		GPIO pin mask pins to be set.
 * 		gpioType	Pin type attribute
 *
 * Note:
 * 		High current drive function is disabled if the pin is configured as an input.
 * 		Internal pullup is disable if the pin is configured as an output
 */
void GPIO_Init(GPIO_Type *pGPIO, uint32_t pinMask, GPIO_PinConfigType gpioType)
{
	if(pGPIO == GPIOA)
	{
		/* Config GPIO for Input or Output */
		if ((gpioType == GPIO_PinOutput) || (gpioType == GPIO_PinOutput_HighCurrent))
		{
			pGPIO->PDDR |= pinMask;      /* Enable Port Data Direction Register */
			pGPIO->PIDR |= pinMask;      /* Set Port Input Disable Register */
		}
		else if ((gpioType == GPIO_PinInput) || (gpioType == GPIO_PinInput_InternalPullup))
		{
			pGPIO->PDDR &= ~pinMask;   /* Disable Port Data Direction Register */
			pGPIO->PIDR &= ~pinMask;   /* Clear Port Input Disable Register */
		}

		switch((uint32_t)pGPIO)
		{
			case GPIOA_BASE:
				if(gpioType == GPIO_PinInput_InternalPullup)
				{
					PORT->PUEL |= pinMask;
				}
				else
				{
					PORT->PUEL &= ~pinMask;
				}
				break;
			default:
				break;
		 }


		/* Config PORT GPIO_PinOutput_HighCurrent for GPIO */
		if (pinMask & GPIO_PTC5_MASK)
		{
			PORT->HDRVE |= PORT_HDRVE_PTC5_MASK;
		}
		if (pinMask & GPIO_PTC1_MASK)
		{
			PORT->HDRVE |= PORT_HDRVE_PTC1_MASK;
		}
		if (pinMask & GPIO_PTB5_MASK)
		{
			PORT->HDRVE |= PORT_HDRVE_PTB5_MASK;
		}
	}
}


/*
 * GPIO_Toggle
 *
 * 		pGPIO 		Pointer to GPIO module, can be GPIOA (MKE04)
 * 		pinMask		GPIO pin mask pins to be set.
 */
void GPIO_Toggle(GPIO_Type *pGPIO, uint32_t pinMask)
{
	if(pGPIO == GPIOA)
	{
		pGPIO->PTOR = pinMask;   /* Toggle the pins specified by pinMask */
	}
}


/*
 * Function: GPIO_Read
 *
 * 		pGPIO		Pointer to GPIO module
 */
uint32_t GPIO_Read(GPIO_Type *pGPIO)
{
	uint32_t rValue;

	rValue = GPIO_INVALID;

    if(pGPIO == GPIOA)
    {
    	rValue = pGPIO->PDIR;   /* Read Port Data Input Register */
    }

    return rValue;
}


/*
 * GPIO_Write
 *
 * 	pGPIO		Pointer to GPIO Module
 * 	value		Value to be written to GPIO
 */
void GPIO_Write(GPIO_Type *pGPIO, uint32_t value)
{
    if(pGPIO == GPIOA)
    {
    	pGPIO->PDOR = value;    /* Write Port Ouput Data Register */
    }

}


/*
 *  Initialize GPIO single pin which is specified by GPIO_Pin
 *
 *  	GPIO_Pin        GPIO pin name, can be GPIO_PTA0,1 ...
 * 	GPIO_PinConfig  Config output or input
 *
 */
void GPIO_PinInit(GPIO_PinType GPIO_Pin, GPIO_PinConfigType GPIO_PinConfig)
{

	if (GPIO_Pin < GPIO_PTE0)
	{
		switch (GPIO_PinConfig)
		{
		case GPIO_PinOutput:
			GPIOA->PDDR |= (1<<GPIO_Pin);      /* Enable Port Data Direction Register */
			GPIOA->PIDR |= (1<<GPIO_Pin);      /* Set Port Input Disable Register */
			PORT->PUEL &= ~(1<<GPIO_Pin);    /* Disable Pullup */
			break;
		case GPIO_PinInput:
			GPIOA->PDDR &= ~(1<<GPIO_Pin);     /* Disable Port Data Direction Register */
			GPIOA->PIDR &= ~(1<<GPIO_Pin);     /* Clear Port Input Disable Register */
			PORT->PUEL &= ~(1<<GPIO_Pin);    /* Disable Pullup */
			break;
		case GPIO_PinInput_InternalPullup:
			GPIOA->PDDR &= ~(1<<GPIO_Pin);     /* Disable Port Data Direction Register */
			GPIOA->PIDR &= ~(1<<GPIO_Pin);     /* Clear Port Input Disable Register */
			PORT->PUEL |= (1<<GPIO_Pin);    /* Enable Pullup */
			break;
		case GPIO_PinOutput_HighCurrent:
			GPIOA->PDDR |= (1<<GPIO_Pin);      /* Enable Port Data Direction Register */
			GPIOA->PIDR |= (1<<GPIO_Pin);      /* Set Port Input Disable Register */
			PORT->PUEL &= ~(1<<GPIO_Pin);    /* Disable Pullup */
			break;
		}
	}

    /* Config GPIO HDRV */
    if(GPIO_PinConfig == GPIO_PinOutput_HighCurrent)
    {
        switch (GPIO_Pin)
        {
            case GPIO_PTB5:
                PORT->HDRVE |= PORT_HDRVE_PTB5_MASK;
                break;
            case GPIO_PTC1:
                PORT->HDRVE |= PORT_HDRVE_PTC1_MASK;
                break;
            case GPIO_PTC5:
                PORT->HDRVE |= PORT_HDRVE_PTC5_MASK;
                break;
            default:
                break;
        }
    }

}

/*
 * Toggle GPIO single pin which is specified by GPIO_Pin
 *
 * 		GPIO_Pin        GPIO pin name, can be GPIO_PTA0,1 ...
 *
 */
void GPIO_PinToggle(GPIO_PinType GPIO_Pin)
{
    if (GPIO_Pin < GPIO_PTE0)
    {
        /* PTA0-7, PTB0-7, PTC0-7, PTD0-7 */
        GPIOA->PTOR = (1<<GPIO_Pin);
    }
}


/*
 * Set GPIO single pin which is specified by GPIO_Pin
 *
 * GPIO_Pin        GPIO pin name, can be GPIO_PTA0,1 ...
 *
 */
void GPIO_PinSet(GPIO_PinType GPIO_Pin)
{
    if (GPIO_Pin < GPIO_PTE0)
    {
        /* PTA0-7, PTB0-7, PTC0-7, PTD0-7 */
        GPIOA->PSOR = (1<<GPIO_Pin);
    }

}

/*
 * Clear GPIO single pin which is specified by GPIO_Pin
 *
 * 	GPIO_Pin        GPIO pin name, can be GPIO_PTA0,1 ...
 *
 */
void GPIO_PinClear(GPIO_PinType GPIO_Pin)
{

    if (GPIO_Pin < GPIO_PTE0)
    {
        /* PTA0-7, PTB0-7, PTC0-7, PTD0-7 */
        GPIOA->PCOR = (1<<GPIO_Pin);
    }
}


