/*
 * mke04z4_gpio.h
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

#ifndef LIBRARIES_MKE04Z8_INCLUDE_MKE04Z4_GPIO_H_
#define LIBRARIES_MKE04Z8_INCLUDE_MKE04Z4_GPIO_H_

typedef enum
{
    GPIO_PinOutput = 0,                 /*!< set pin as outout */
    GPIO_PinInput,                      /*!< set pin as input */
    GPIO_PinInput_InternalPullup,       /*!< set internal pullup for input pin */
    GPIO_PinOutput_HighCurrent,         /*!< set high drive for output pin */
} GPIO_PinConfigType;

typedef enum
{
    /* in GPIOA register */
    GPIO_PTA0_MASK = (1<<0),    /*!< GPIO Pin PTA0 bit mask */
    GPIO_PTA1_MASK = (1<<1),    /*!< GPIO Pin PTA1 bit mask */
    GPIO_PTA2_MASK = (1<<2),    /*!< GPIO Pin PTA2 bit mask */
    GPIO_PTA3_MASK = (1<<3),    /*!< GPIO Pin PTA3 bit mask */
    GPIO_PTA4_MASK = (1<<4),    /*!< GPIO Pin PTA4 bit mask */
    GPIO_PTA5_MASK = (1<<5),    /*!< GPIO Pin PTA5 bit mask */
    GPIO_PTA6_MASK = (1<<6),    /*!< GPIO Pin PTA6 bit mask */
    GPIO_PTA7_MASK = (1<<7),    /*!< GPIO Pin PTA7 bit mask */
    GPIO_PTB0_MASK = (1<<8),    /*!< GPIO Pin PTB0 bit mask */
    GPIO_PTB1_MASK = (1<<9),    /*!< GPIO Pin PTB1 bit mask */
    GPIO_PTB2_MASK = (1<<10),   /*!< GPIO Pin PTB2 bit mask */
    GPIO_PTB3_MASK = (1<<11),   /*!< GPIO Pin PTB3 bit mask */
    GPIO_PTB4_MASK = (1<<12),   /*!< GPIO Pin PTB4 bit mask */
    GPIO_PTB5_MASK = (1<<13),   /*!< GPIO Pin PTB5 bit mask */
    GPIO_PTB6_MASK = (1<<14),   /*!< GPIO Pin PTB6 bit mask */
    GPIO_PTB7_MASK = (1<<15),   /*!< GPIO Pin PTB7 bit mask */
    GPIO_PTC0_MASK = (1<<16),   /*!< GPIO Pin PTC0 bit mask */
    GPIO_PTC1_MASK = (1<<17),   /*!< GPIO Pin PTC1 bit mask */
    GPIO_PTC2_MASK = (1<<18),   /*!< GPIO Pin PTC2 bit mask */
    GPIO_PTC3_MASK = (1<<19),   /*!< GPIO Pin PTC3 bit mask */
    GPIO_PTC4_MASK = (1<<20),   /*!< GPIO Pin PTC4 bit mask */
    GPIO_PTC5_MASK = (1<<21),   /*!< GPIO Pin PTC5 bit mask */
    GPIO_PTC6_MASK = (1<<22),   /*!< GPIO Pin PTC6 bit mask */
    GPIO_PTC7_MASK = (1<<23),   /*!< GPIO Pin PTC7 bit mask */
    GPIO_PTD0_MASK = (1<<24),   /*!< GPIO Pin PTD0 bit mask */
    GPIO_PTD1_MASK = (1<<25),   /*!< GPIO Pin PTD1 bit mask */
    GPIO_PTD2_MASK = (1<<26),   /*!< GPIO Pin PTD2 bit mask */
    GPIO_PTD3_MASK = (1<<27),   /*!< GPIO Pin PTD3 bit mask */
    GPIO_PTD4_MASK = (1<<28),   /*!< GPIO Pin PTD4 bit mask */
    GPIO_PTD5_MASK = (1<<29),   /*!< GPIO Pin PTD5 bit mask */
    GPIO_PTD6_MASK = (1<<30),   /*!< GPIO Pin PTD6 bit mask */
    GPIO_PTD7_MASK = (1<<31),   /*!< GPIO Pin PTD7 bit mask */
    /* in GPIOB register */
    GPIO_PTE0_MASK = (1<<0),    /*!< GPIO Pin PTE0 bit mask */
    GPIO_PTE1_MASK = (1<<1),    /*!< GPIO Pin PTE1 bit mask */
    GPIO_PTE2_MASK = (1<<2),    /*!< GPIO Pin PTE2 bit mask */
    GPIO_PTE3_MASK = (1<<3),    /*!< GPIO Pin PTE3 bit mask */
    GPIO_PTE4_MASK = (1<<4),    /*!< GPIO Pin PTE4 bit mask */
    GPIO_PTE5_MASK = (1<<5),    /*!< GPIO Pin PTE5 bit mask */
    GPIO_PTE6_MASK = (1<<6),    /*!< GPIO Pin PTE6 bit mask */
    GPIO_PTE7_MASK = (1<<7),    /*!< GPIO Pin PTE7 bit mask */
    GPIO_PTF0_MASK = (1<<8),    /*!< GPIO Pin PTF0 bit mask */
    GPIO_PTF1_MASK = (1<<9),    /*!< GPIO Pin PTF1 bit mask */
    GPIO_PTF2_MASK = (1<<10),   /*!< GPIO Pin PTF2 bit mask */
    GPIO_PTF3_MASK = (1<<11),   /*!< GPIO Pin PTF3 bit mask */
    GPIO_PTF4_MASK = (1<<12),   /*!< GPIO Pin PTF4 bit mask */
    GPIO_PTF5_MASK = (1<<13),   /*!< GPIO Pin PTF5 bit mask */
    GPIO_PTF6_MASK = (1<<14),   /*!< GPIO Pin PTF6 bit mask */
    GPIO_PTF7_MASK = (1<<15),   /*!< GPIO Pin PTF7 bit mask */
    GPIO_PTG0_MASK = (1<<16),   /*!< GPIO Pin PTG0 bit mask */
    GPIO_PTG1_MASK = (1<<17),   /*!< GPIO Pin PTG1 bit mask */
    GPIO_PTG2_MASK = (1<<18),   /*!< GPIO Pin PTG2 bit mask */
    GPIO_PTG3_MASK = (1<<19),   /*!< GPIO Pin PTG3 bit mask */
    GPIO_PTG4_MASK = (1<<20),   /*!< GPIO Pin PTG4 bit mask */
    GPIO_PTG5_MASK = (1<<21),   /*!< GPIO Pin PTG5 bit mask */
    GPIO_PTG6_MASK = (1<<22),   /*!< GPIO Pin PTG6 bit mask */
    GPIO_PTG7_MASK = (1<<23),   /*!< GPIO Pin PTG7 bit mask */
    GPIO_PTH0_MASK = (1<<24),   /*!< GPIO Pin PTH0 bit mask */
    GPIO_PTH1_MASK = (1<<25),   /*!< GPIO Pin PTH1 bit mask */
    GPIO_PTH2_MASK = (1<<26),   /*!< GPIO Pin PTH2 bit mask */
    GPIO_PTH3_MASK = (1<<27),   /*!< GPIO Pin PTH3 bit mask */
    GPIO_PTH4_MASK = (1<<28),   /*!< GPIO Pin PTH4 bit mask */
    GPIO_PTH5_MASK = (1<<29),   /*!< GPIO Pin PTH5 bit mask */
    GPIO_PTH6_MASK = (1<<30),   /*!< GPIO Pin PTH6 bit mask */
    GPIO_PTH7_MASK = (1<<31),   /*!< GPIO Pin PTH7 bit mask */
    /* in GPIOC register */
    GPIO_PTI0_MASK = (1<<0),    /*!< GPIO Pin PTI0 bit mask */
    GPIO_PTI1_MASK = (1<<1),    /*!< GPIO Pin PTI1 bit mask */
    GPIO_PTI2_MASK = (1<<2),    /*!< GPIO Pin PTI2 bit mask */
    GPIO_PTI3_MASK = (1<<3),    /*!< GPIO Pin PTI3 bit mask */
    GPIO_PTI4_MASK = (1<<4),    /*!< GPIO Pin PTI4 bit mask */
    GPIO_PTI5_MASK = (1<<5),    /*!< GPIO Pin PTI5 bit mask */
    GPIO_PTI6_MASK = (1<<6),    /*!< GPIO Pin PTI6 bit mask */
    GPIO_PTI7_MASK = (1<<7),    /*!< GPIO Pin PTI7 bit mask */
} GPIO_PinMaskType;

typedef enum
{
    /* in GPIOA register */
    GPIO_PTA0 = 0,              /*!< GPIO Pin PTA0 */
    GPIO_PTA1,                  /*!< GPIO Pin PTA1 */
    GPIO_PTA2,                  /*!< GPIO Pin PTA2 */
    GPIO_PTA3,                  /*!< GPIO Pin PTA3 */
    GPIO_PTA4,                  /*!< GPIO Pin PTA4 */
    GPIO_PTA5,                  /*!< GPIO Pin PTA5 */
    GPIO_PTA6,                  /*!< GPIO Pin PTA6 */
    GPIO_PTA7,                  /*!< GPIO Pin PTA7 */
    GPIO_PTB0,                  /*!< GPIO Pin PTB0 */
    GPIO_PTB1,                  /*!< GPIO Pin PTB1 */
    GPIO_PTB2,                  /*!< GPIO Pin PTB2 */
    GPIO_PTB3,                  /*!< GPIO Pin PTB3 */
    GPIO_PTB4,                  /*!< GPIO Pin PTB4 */
    GPIO_PTB5,                  /*!< GPIO Pin PTB5 */
    GPIO_PTB6,                  /*!< GPIO Pin PTB6 */
    GPIO_PTB7,                  /*!< GPIO Pin PTB7 */
    GPIO_PTC0,                  /*!< GPIO Pin PTC0 */
    GPIO_PTC1,                  /*!< GPIO Pin PTC1 */
    GPIO_PTC2,                  /*!< GPIO Pin PTC2 */
    GPIO_PTC3,                  /*!< GPIO Pin PTC3 */
    GPIO_PTC4,                  /*!< GPIO Pin PTC4 */
    GPIO_PTC5,                  /*!< GPIO Pin PTC5 */
    GPIO_PTC6,                  /*!< GPIO Pin PTC6 */
    GPIO_PTC7,                  /*!< GPIO Pin PTC7 */
    GPIO_PTD0,                  /*!< GPIO Pin PTD0 */
    GPIO_PTD1,                  /*!< GPIO Pin PTD1 */
    GPIO_PTD2,                  /*!< GPIO Pin PTD2 */
    GPIO_PTD3,                  /*!< GPIO Pin PTD3 */
    GPIO_PTD4,                  /*!< GPIO Pin PTD4 */
    GPIO_PTD5,                  /*!< GPIO Pin PTD5 */
    GPIO_PTD6,                  /*!< GPIO Pin PTD6 */
    GPIO_PTD7,                  /*!< GPIO Pin PTD7 */
    /* in GPIOB register */
    GPIO_PTE0,                  /*!< GPIO Pin PTE0 */
    GPIO_PTE1,                  /*!< GPIO Pin PTE1 */
    GPIO_PTE2,                  /*!< GPIO Pin PTE2 */
    GPIO_PTE3,                  /*!< GPIO Pin PTE3 */
    GPIO_PTE4,                  /*!< GPIO Pin PTE4 */
    GPIO_PTE5,                  /*!< GPIO Pin PTE5 */
    GPIO_PTE6,                  /*!< GPIO Pin PTE6 */
    GPIO_PTE7,                  /*!< GPIO Pin PTE7 */
    GPIO_PTF0,                  /*!< GPIO Pin PTF0 */
    GPIO_PTF1,                  /*!< GPIO Pin PTF1 */
    GPIO_PTF2,                  /*!< GPIO Pin PTF2 */
    GPIO_PTF3,                  /*!< GPIO Pin PTF3 */
    GPIO_PTF4,                  /*!< GPIO Pin PTF4 */
    GPIO_PTF5,                  /*!< GPIO Pin PTF5 */
    GPIO_PTF6,                  /*!< GPIO Pin PTF6 */
    GPIO_PTF7,                  /*!< GPIO Pin PTF7 */
    GPIO_PTG0,                  /*!< GPIO Pin PTG0 */
    GPIO_PTG1,                  /*!< GPIO Pin PTG1 */
    GPIO_PTG2,                  /*!< GPIO Pin PTG2 */
    GPIO_PTG3,                  /*!< GPIO Pin PTG3 */
    GPIO_PTG4,                  /*!< GPIO Pin PTG4 */
    GPIO_PTG5,                  /*!< GPIO Pin PTG5 */
    GPIO_PTG6,                  /*!< GPIO Pin PTG6 */
    GPIO_PTG7,                  /*!< GPIO Pin PTG7 */
    GPIO_PTH0,                  /*!< GPIO Pin PTH0 */
    GPIO_PTH1,                  /*!< GPIO Pin PTH1 */
    GPIO_PTH2,                  /*!< GPIO Pin PTH2 */
    GPIO_PTH3,                  /*!< GPIO Pin PTH3 */
    GPIO_PTH4,                  /*!< GPIO Pin PTH4 */
    GPIO_PTH5,                  /*!< GPIO Pin PTH5 */
    GPIO_PTH6,                  /*!< GPIO Pin PTH6 */
    GPIO_PTH7,                  /*!< GPIO Pin PTH7 */
    /* the following pins are not in KE02 */
    GPIO_PTI0,                  /*!< GPIO Pin PTI0 */
    GPIO_PTI1,                  /*!< GPIO Pin PTI1 */
    GPIO_PTI2,                  /*!< GPIO Pin PTI2 */
    GPIO_PTI3,                  /*!< GPIO Pin PTI3 */
    GPIO_PTI4,                  /*!< GPIO Pin PTI4 */
    GPIO_PTI5,                  /*!< GPIO Pin PTI5 */
    GPIO_PTI6,                  /*!< GPIO Pin PTI6 */
    GPIO_PTI7,                  /*!< GPIO Pin PTI7 */
    GPIO_PIN_MAX,
} GPIO_PinType;


#define GPIO_INVALID 0xFFFFFFFF


void GPIO_DeInit(GPIO_Type *pGPIO);
void GPIO_Init(GPIO_Type *pGPIO, uint32_t pinMask, GPIO_PinConfigType gpioType);
void GPIO_Toggle(GPIO_Type *pGPIO, uint32_t pinMask);
void GPIO_Write(GPIO_Type *pGPIO, uint32_t value);
void GPIO_PinInit(GPIO_PinType GPIO_Pin, GPIO_PinConfigType GPIO_PinConfig);
void GPIO_PinToggle(GPIO_PinType GPIO_Pin);



#endif /* LIBRARIES_MKE04Z8_INCLUDE_MKE04Z4_GPIO_H_ */
