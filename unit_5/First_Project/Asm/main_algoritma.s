	.cpu arm7tdmi
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"main_algoritma.c"
	.text
	.comm	Main_Al_State,1,1
	.comm	Pressure_Value,4,4
	.global	Threshold
	.data
	.align	2
	.type	Threshold, %object
	.size	Threshold, 4
Threshold:
	.word	20
	.global	Main_p_fun
	.align	2
	.type	Main_p_fun, %object
	.size	Main_p_fun, 4
Main_p_fun:
	.word	Algoritma_Data_waiting
	.text
	.align	2
	.global	Algoritma_Data_waiting
	.arch armv4t
	.syntax unified
	.arm
	.fpu softvfp
	.type	Algoritma_Data_waiting, %function
Algoritma_Data_waiting:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	nop
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	Algoritma_Data_waiting, .-Algoritma_Data_waiting
	.align	2
	.global	Algoritma_Calculate_data
	.syntax unified
	.arm
	.fpu softvfp
	.type	Algoritma_Calculate_data, %function
Algoritma_Calculate_data:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	ldr	r3, .L4
	ldr	r2, [r3]
	ldr	r3, .L4+4
	ldr	r3, [r3]
	cmp	r2, r3
	bls	.L3
	bl	Timer_starting
.L3:
	ldr	r3, .L4+8
	ldr	r2, .L4+12
	str	r2, [r3]
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, lr}
	bx	lr
.L5:
	.align	2
.L4:
	.word	Pressure_Value
	.word	Threshold
	.word	Main_p_fun
	.word	Algoritma_Data_waiting
	.size	Algoritma_Calculate_data, .-Algoritma_Calculate_data
	.align	2
	.global	Send_pressure_value
	.syntax unified
	.arm
	.fpu softvfp
	.type	Send_pressure_value, %function
Send_pressure_value:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	str	r0, [fp, #-8]
	ldr	r2, .L7
	ldr	r3, [fp, #-8]
	str	r3, [r2]
	ldr	r3, .L7+4
	ldr	r2, .L7+8
	str	r2, [r3]
	nop
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
.L8:
	.align	2
.L7:
	.word	Pressure_Value
	.word	Main_p_fun
	.word	Algoritma_Calculate_data
	.size	Send_pressure_value, .-Send_pressure_value
	.ident	"GCC: (GNU Tools for STM32 9-2020-q2-update.20201001-1621) 9.3.1 20200408 (release)"
