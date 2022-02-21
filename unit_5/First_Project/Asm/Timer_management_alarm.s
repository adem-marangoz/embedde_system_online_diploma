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
	.file	"Timer_management_alarm.c"
	.text
	.comm	Timer_state,1,1
	.bss
	.align	2
counter1:
	.space	4
	.size	counter1, 4
	.global	Timer_p_fun
	.data
	.align	2
	.type	Timer_p_fun, %object
	.size	Timer_p_fun, 4
Timer_p_fun:
	.word	Timer_Timer_Alarm_Off
	.text
	.align	2
	.global	Timer_Timer_Alarm_Off
	.arch armv4t
	.syntax unified
	.arm
	.fpu softvfp
	.type	Timer_Timer_Alarm_Off, %function
Timer_Timer_Alarm_Off:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	mov	r0, #0
	bl	Alarm_on_off_fun
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, lr}
	bx	lr
	.size	Timer_Timer_Alarm_Off, .-Timer_Timer_Alarm_Off
	.align	2
	.global	Timer_Timer_Alarm_On
	.syntax unified
	.arm
	.fpu softvfp
	.type	Timer_Timer_Alarm_On, %function
Timer_Timer_Alarm_On:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	ldr	r3, .L5
	ldr	r3, [r3]
	add	r3, r3, #1
	ldr	r2, .L5
	str	r3, [r2]
	ldr	r3, .L5
	ldr	r3, [r3]
	ldr	r2, .L5+4
	cmp	r3, r2
	bne	.L4
	ldr	r3, .L5
	mov	r2, #0
	str	r2, [r3]
	ldr	r3, .L5+8
	ldr	r2, .L5+12
	str	r2, [r3]
	ldr	r3, .L5+8
	ldr	r3, [r3]
	mov	lr, pc
	bx	r3
.L4:
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, lr}
	bx	lr
.L6:
	.align	2
.L5:
	.word	counter1
	.word	50003
	.word	Timer_p_fun
	.word	Timer_Timer_Alarm_Off
	.size	Timer_Timer_Alarm_On, .-Timer_Timer_Alarm_On
	.align	2
	.global	Timer_starting
	.syntax unified
	.arm
	.fpu softvfp
	.type	Timer_starting, %function
Timer_starting:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	ldr	r3, .L8
	ldr	r2, .L8+4
	str	r2, [r3]
	mov	r0, #1
	bl	Alarm_on_off_fun
	ldr	r3, .L8+8
	mov	r2, #0
	str	r2, [r3]
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, lr}
	bx	lr
.L9:
	.align	2
.L8:
	.word	Timer_p_fun
	.word	Timer_Timer_Alarm_On
	.word	counter1
	.size	Timer_starting, .-Timer_starting
	.ident	"GCC: (GNU Tools for STM32 9-2020-q2-update.20201001-1621) 9.3.1 20200408 (release)"
