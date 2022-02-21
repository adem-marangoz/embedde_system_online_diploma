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
	.file	"main.c"
	.text
	.comm	Main_Al_State,1,1
	.comm	Pressure_state,1,1
	.comm	Timer_state,1,1
	.align	2
	.global	setup
	.arch armv4t
	.syntax unified
	.arm
	.fpu softvfp
	.type	setup, %function
setup:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	bl	init_Pressure
	bl	Alarm_init
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, lr}
	bx	lr
	.size	setup, .-setup
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	bl	setup
.L4:
	ldr	r3, .L5
	ldr	r3, [r3]
	mov	lr, pc
	bx	r3
	ldr	r3, .L5+4
	ldr	r3, [r3]
	mov	lr, pc
	bx	r3
	ldr	r3, .L5+8
	ldr	r3, [r3]
	mov	lr, pc
	bx	r3
	ldr	r3, .L5+12
	ldrb	r2, [r3]	@ zero_extendqisi2
	ldr	r3, .L5+16
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r2, r3
	beq	.L4
	ldr	r3, .L5+20
	ldr	r3, [r3]
	mov	lr, pc
	bx	r3
	b	.L4
.L6:
	.align	2
.L5:
	.word	Pressure_P_fun
	.word	Main_p_fun
	.word	Timer_p_fun
	.word	Prev_Alarm_state
	.word	Curr_Alarm_state
	.word	Alarm_p_fun
	.size	main, .-main
	.ident	"GCC: (GNU Tools for STM32 9-2020-q2-update.20201001-1621) 9.3.1 20200408 (release)"
