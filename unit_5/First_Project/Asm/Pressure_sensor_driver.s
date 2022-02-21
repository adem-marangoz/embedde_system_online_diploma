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
	.file	"Pressure_sensor_driver.c"
	.text
	.comm	Pressure_state,1,1
	.global	Pressure_P_fun
	.data
	.align	2
	.type	Pressure_P_fun, %object
	.size	Pressure_P_fun, 4
Pressure_P_fun:
	.word	Pr_Reading_and_sending
	.comm	Pressure_Value,4,4
	.text
	.align	2
	.global	init_Pressure
	.arch armv4t
	.syntax unified
	.arm
	.fpu softvfp
	.type	init_Pressure, %function
init_Pressure:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	ldr	r3, .L2
	ldr	r3, [r3]
	ldr	r2, .L2
	orr	r3, r3, #4
	str	r3, [r2]
	ldr	r3, .L2+4
	ldr	r3, [r3]
	ldr	r2, .L2+4
	bic	r3, r3, #15728640
	str	r3, [r2]
	ldr	r3, .L2+4
	ldr	r2, .L2+4
	ldr	r3, [r3]
	str	r3, [r2]
	nop
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
.L3:
	.align	2
.L2:
	.word	1073877016
	.word	1073809408
	.size	init_Pressure, .-init_Pressure
	.align	2
	.global	Pr_Reading_and_sending
	.syntax unified
	.arm
	.fpu softvfp
	.type	Pr_Reading_and_sending, %function
Pr_Reading_and_sending:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	ldr	r3, .L5
	ldr	r3, [r3]
	and	r3, r3, #255
	ldr	r2, .L5+4
	str	r3, [r2]
	ldr	r3, .L5+4
	ldr	r3, [r3]
	mov	r0, r3
	bl	Send_pressure_value
	ldr	r3, .L5+8
	ldr	r2, .L5+12
	str	r2, [r3]
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, lr}
	bx	lr
.L6:
	.align	2
.L5:
	.word	1073809416
	.word	Pressure_Value
	.word	Pressure_P_fun
	.word	Pr_Waiting
	.size	Pr_Reading_and_sending, .-Pr_Reading_and_sending
	.align	2
	.global	Pr_Waiting
	.syntax unified
	.arm
	.fpu softvfp
	.type	Pr_Waiting, %function
Pr_Waiting:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	ldr	r3, .L10
	ldr	r3, [r3]
	add	r3, r3, #1
	ldr	r2, .L10
	str	r3, [r2]
	ldr	r3, .L10
	ldr	r3, [r3]
	ldr	r2, .L10+4
	cmp	r3, r2
	bne	.L9
	ldr	r3, .L10
	mov	r2, #0
	str	r2, [r3]
	ldr	r3, .L10+8
	ldr	r2, .L10+12
	str	r2, [r3]
.L9:
	nop
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
.L11:
	.align	2
.L10:
	.word	counter.5236
	.word	50000
	.word	Pressure_P_fun
	.word	Pr_Reading_and_sending
	.size	Pr_Waiting, .-Pr_Waiting
	.bss
	.align	2
counter.5236:
	.space	4
	.size	counter.5236, 4
	.ident	"GCC: (GNU Tools for STM32 9-2020-q2-update.20201001-1621) 9.3.1 20200408 (release)"
