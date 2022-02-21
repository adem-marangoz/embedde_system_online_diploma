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
	.file	"Alarm_driver.c"
	.text
	.comm	Prev_Alarm_state,1,1
	.comm	Curr_Alarm_state,1,1
	.global	Alarm_p_fun
	.data
	.align	2
	.type	Alarm_p_fun, %object
	.size	Alarm_p_fun, 4
Alarm_p_fun:
	.word	Al_Alarm_Off
	.text
	.align	2
	.global	Alarm_init
	.arch armv4t
	.syntax unified
	.arm
	.fpu softvfp
	.type	Alarm_init, %function
Alarm_init:
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
	ldr	r2, [r3]
	ldr	r1, .L2+4
	ldr	r3, .L2+8
	orr	r3, r2, r3
	str	r3, [r1]
	ldr	r3, .L2+12
	mov	r2, #0
	strb	r2, [r3]
	ldr	r3, .L2+16
	mov	r2, #0
	strb	r2, [r3]
	ldr	r3, .L2+20
	ldr	r2, .L2+24
	str	r2, [r3]
	nop
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
.L3:
	.align	2
.L2:
	.word	1073877016
	.word	1073809412
	.word	572662306
	.word	Prev_Alarm_state
	.word	Curr_Alarm_state
	.word	Alarm_p_fun
	.word	Al_Alarm_Off
	.size	Alarm_init, .-Alarm_init
	.align	2
	.global	Al_Alarm_Off
	.syntax unified
	.arm
	.fpu softvfp
	.type	Al_Alarm_Off, %function
Al_Alarm_Off:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	ldr	r3, .L5
	ldr	r3, [r3]
	ldr	r2, .L5
	orr	r3, r3, #8192
	str	r3, [r2]
	ldr	r3, .L5+4
	mov	r2, #0
	strb	r2, [r3]
	ldr	r3, .L5+8
	mov	r2, #0
	strb	r2, [r3]
	nop
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
.L6:
	.align	2
.L5:
	.word	1073809420
	.word	Prev_Alarm_state
	.word	Curr_Alarm_state
	.size	Al_Alarm_Off, .-Al_Alarm_Off
	.align	2
	.global	Al_Alarm_On
	.syntax unified
	.arm
	.fpu softvfp
	.type	Al_Alarm_On, %function
Al_Alarm_On:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	ldr	r3, .L8
	ldr	r3, [r3]
	ldr	r2, .L8
	bic	r3, r3, #8192
	str	r3, [r2]
	ldr	r3, .L8+4
	mov	r2, #1
	strb	r2, [r3]
	ldr	r3, .L8+8
	mov	r2, #1
	strb	r2, [r3]
	nop
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
.L9:
	.align	2
.L8:
	.word	1073809420
	.word	Prev_Alarm_state
	.word	Curr_Alarm_state
	.size	Al_Alarm_On, .-Al_Alarm_On
	.align	2
	.global	Alarm_on_off_fun
	.syntax unified
	.arm
	.fpu softvfp
	.type	Alarm_on_off_fun, %function
Alarm_on_off_fun:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	mov	r3, r0
	strb	r3, [fp, #-5]
	ldr	r3, .L14
	mov	r2, #0
	strb	r2, [r3]
	ldr	r3, .L14+4
	mov	r2, #1
	strb	r2, [r3]
	ldrb	r3, [fp, #-5]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L11
	ldr	r3, .L14+8
	ldr	r2, .L14+12
	str	r2, [r3]
	b	.L13
.L11:
	ldr	r3, .L14+8
	ldr	r2, .L14+16
	str	r2, [r3]
.L13:
	nop
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
.L15:
	.align	2
.L14:
	.word	Prev_Alarm_state
	.word	Curr_Alarm_state
	.word	Alarm_p_fun
	.word	Al_Alarm_Off
	.word	Al_Alarm_On
	.size	Alarm_on_off_fun, .-Alarm_on_off_fun
	.ident	"GCC: (GNU Tools for STM32 9-2020-q2-update.20201001-1621) 9.3.1 20200408 (release)"
