/* File: startup_ARMCM0.S
 * Purpose: startup file for Cortex-M0 devices. Should use with
 *   GCC for ARM Embedded Processors
 * Version: V2.0
 * Date: 16 August 2013
 *
/* Copyright (c) 2011 - 2013 ARM LIMITED

   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   - Neither the name of ARM nor the names of its contributors may be used
     to endorse or promote products derived from this software without
     specific prior written permission.
   *
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
   ---------------------------------------------------------------------------*/
	.syntax	unified
	.arch	armv6-m

	.section .stack
	.align	3

.equ	__STARTUP_CLEAR_BSS, 1

.ifdef __STACK_SIZE
	.equ	Stack_Size, __STACK_SIZE
.else
	.equ	Stack_Size, 0x040
.endif
	.globl	__StackTop
	.globl	__StackLimit
__StackLimit:
	.space	Stack_Size
	.size	__StackLimit, . - __StackLimit
__StackTop:
	.size	__StackTop, . - __StackTop

	.section .heap
	.align	3
.ifdef __HEAP_SIZE
	.equ	Heap_Size, __HEAP_SIZE
.else
	.equ	Heap_Size, 0
.endif

	.globl	__HeapBase
	.globl	__HeapLimit
__HeapBase:
	.if	Heap_Size
	.space	Heap_Size
	.endif
	.size	__HeapBase, . - __HeapBase
__HeapLimit:
	.size	__HeapLimit, . - __HeapLimit

	.section .isr_vector
	.align 2
	.globl	__isr_vector
__isr_vector:
	.long	__stack            	  	/* 0 - Top of Stack */
	.long	Reset_Handler         	/* 1 - Reset interrupt */
	.long	NMI_Handler           	/* 2 - NMI interrupt */
	.long	HardFault_Handler     	/* 3 - Hard Fault interrupt */
	.long	0                     	/* 4 - Reserved */
	.long	0                     	/* 5 - Reserved */
	.long	0                     	/* 6 - Reserved */
	.long	0                     	/* 7 - Reserved */
	.long	0                     	/* 8 - Reserved */
	.long	0                     	/* 9 - Reserved */
	.long	0                     	/* 10 - Reserved */
	.long	SVC_Handler           	/* 11 - SVCall interrupt */
	.long	0                     	/* 12 - Reserved */
	.long	0                     	/* 13 - Reserved */
	.long	PendSV_Handler        	/* 14 - PendSV interrupt */
	.long	SysTick_Handler       	/* 15 - SysTick interrupt */

	/* External interrupts */
	.long	Default_Handler			/* 16 - Reserved */
	.long	0						/* 17 - Reserved */
	.long	0						/* 18 - Reserved */
	.long	0						/* 19 - Reserved */
	.long	0						/* 20 - Reserved */
	.long	FTMRE_Handler			/* 21 - Command complete interrupt */
	.long	PMC_Handler				/* 22 - Low-voltage warning interrupt */
	.long 	IRQ_Handler				/* 23 - External interrupt */
	.long	I2C0_Handler			/* 24 - I2C0 interrupt */
	.long	0						/* 25 - Reserved */
	.long	SPI0_Handler			/* 26 - SPI0 interrupt */
	.long	0						/* 27 - Reserved */
	.long	UART0_Handler			/* 28 - UART0 interrupt */
	.long	0						/* 29 - Reserved */
	.long	0						/* 30 - Reserved */
	.long	ADC0_Handler			/* 31 - ADC Conversion Complete interrupt */
	.long	ACMP0_Handler			/* 32 - Analog comparator 0 interrupt */
	.long	FTM0_Handler			/* 33 - FTM0 interrupt */
	.long	0						/* 34 - Reserved */
	.long	FTM2_Handler			/* 35 - FTM2 interrupt */
	.long	RTC_Handler				/* 36 - RTC overflow interrupt */
	.long 	ACMP1_Handler			/* 37 - Analog comparator 1 interrupt */
	.long	PIT_CH0_Handler			/* 38 - PIT CH0 overflow */
	.long	PIT_CH1_Handler			/* 39 - PIT CH1 overflow */
	.long	KBI0_Handler			/* 40 - Keyboard 0 interrupt */
	.long	KBI1_Handler			/* 41 - Keyboard 1 interrupt */
	.long	0						/* 42 - Reserved */
	.long	ICS_Handler				/* 43 - Clock loss of lock */
	.long	WDOG_Handler			/* 44 - Watchdog timeout */
	.long	PWT_Handler				/* 45 - PWT interrupt */

	.size	__isr_vector, . - __isr_vector

	.text
	.thumb
	.thumb_func
	.align	1
	.globl	Reset_Handler
	.type	Reset_Handler, %function
Reset_Handler:
/*  Firstly it copies data from read only memory to RAM. There are two schemes
 *  to copy. One can copy more than one sections. Another can only copy
 *  one section.  The former scheme needs more instructions and read-only
 *  data to implement than the latter.
 *  Macro __STARTUP_COPY_MULTIPLE is used to choose between two schemes.  */

.ifdef __STARTUP_COPY_MULTIPLE
/*  Multiple sections scheme.
 *
 *  Between symbol address __copy_table_start__ and __copy_table_end__,
 *  there are array of triplets, each of which specify:
 *    offset 0: LMA of start of a section to copy from
 *    offset 4: VMA of start of a section to copy to
 *    offset 8: size of the section to copy. Must be multiply of 4
 *
 *  All addresses must be aligned to 4 bytes boundary.
*/
	ldr	r4, =__copy_table_start__
	ldr	r5, =__copy_table_end__

.L_loop0:
	cmp	r4, r5
	bge	.L_loop0_done
	ldr	r1, [r4]
	ldr	r2, [r4, #4]
	ldr	r3, [r4, #8]

.L_loop0_0:
	subs	r3, #4
	blt	.L_loop0_0_done
	ldr	r0, [r1, r3]
	str	r0, [r2, r3]
	b	.L_loop0_0

.L_loop0_0_done:
	adds	r4, #12
	b	.L_loop0

.L_loop0_done:

.else
/*  Single section scheme.
 *
 *  The ranges of copy from/to are specified by following symbols
 *    __etext: LMA of start of the section to copy from. Usually end of text
 *    __data_start__: VMA of start of the section to copy to
 *    __data_end__: VMA of end of the section to copy to
 *
 *  All addresses must be aligned to 4 bytes boundary.
 */
	ldr	r1, =__etext
	ldr	r2, =__data_start__
	ldr	r3, =__data_end__

	subs	r3, r2
	ble	.L_loop1_done

.L_loop1:
	subs	r3, #4
	ldr	r0, [r1,r3]
	str	r0, [r2,r3]
	bgt	.L_loop1

.L_loop1_done:
.endif /*__STARTUP_COPY_MULTIPLE */

/*  This part of work usually is done in C library startup code. Otherwise,
 *  define this macro to enable it in this startup.
 *
 *  There are two schemes too. One can clear multiple BSS sections. Another
 *  can only clear one section. The former is more size expensive than the
 *  latter.
 *
 *  Define macro __STARTUP_CLEAR_BSS_MULTIPLE to choose the former.
 *  Otherwise efine macro __STARTUP_CLEAR_BSS to choose the later.
 */
.ifdef __STARTUP_CLEAR_BSS_MULTIPLE
/*  Multiple sections scheme.
 *
 *  Between symbol address __copy_table_start__ and __copy_table_end__,
 *  there are array of tuples specifying:
 *    offset 0: Start of a BSS section
 *    offset 4: Size of this BSS section. Must be multiply of 4
 */
	ldr	r3, =__zero_table_start__
	ldr	r4, =__zero_table_end__

.L_loop2:
	cmp	r3, r4
	bge	.L_loop2_done
	ldr	r1, [r3]
	ldr	r2, [r3, #4]
	movs	r0, 0

.L_loop2_0:
	subs	r2, #4
	blt	.L_loop2_0_done
	str	r0, [r1, r2]
	b	.L_loop2_0
.L_loop2_0_done:

	adds	r3, #8
	b	.L_loop2
.L_loop2_done:
.endif
/* .elif defined (__STARTUP_CLEAR_BSS) */
.ifdef __STARTUP_CLEAR_BSS
/*  Single BSS section scheme.
 *
 *  The BSS section is specified by following symbols
 *    __bss_start__: start of the BSS section.
 *    __bss_end__: end of the BSS section.
 *
 *  Both addresses must be aligned to 4 bytes boundary.
 */
	ldr	r1, =__bss_start__
	ldr	r2, =__bss_end__

	movs	r0, 0

	subs	r2, r1
	ble	.L_loop3_done

.L_loop3:
	subs	r2, #4
	str	r0, [r1, r2]
	bgt	.L_loop3
.L_loop3_done:
.endif /* __STARTUP_CLEAR_BSS_MULTIPLE || __STARTUP_CLEAR_BSS */

.ifndef __NO_SYSTEM_INIT
	bl	SystemInit
.endif

.ifndef __START
/* .set __START, _start */
.set __START, main
.endif
	bl	__START
	/* bl main */

	.pool
	.size	Reset_Handler, . - Reset_Handler

	.align	1
	.thumb_func
	.weak	Default_Handler
	.type	Default_Handler, %function
Default_Handler:
	b	.
	.size	Default_Handler, . - Default_Handler

/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
	.macro	def_irq_handler	handler_name
	.weak	\handler_name
	.set	\handler_name, Default_Handler
	.endm

	def_irq_handler	NMI_Handler
	def_irq_handler	HardFault_Handler
	def_irq_handler	SVC_Handler
	def_irq_handler	PendSV_Handler
	def_irq_handler	SysTick_Handler
	def_irq_handler	DEF_IRQHandler
	def_irq_handler	FTMRE_Handler
	def_irq_handler	PMC_Handler
	def_irq_handler	IRQ_Handler
	def_irq_handler	I2C0_Handler
	def_irq_handler	SPI0_Handler
	def_irq_handler	UART0_Handler
	def_irq_handler ADC0_Handler
	def_irq_handler ACMP0_Handler
	def_irq_handler FTM0_Handler
	def_irq_handler FTM2_Handler
	def_irq_handler RTC_Handler
	def_irq_handler ACMP1_Handler
	def_irq_handler PIT_CH0_Handler
	def_irq_handler	PIT_CH1_Handler
	def_irq_handler KBI0_Handler
	def_irq_handler KBI1_Handler
	def_irq_handler ICS_Handler
	def_irq_handler WDOG_Handler
	def_irq_handler PWT_Handler


	.end
