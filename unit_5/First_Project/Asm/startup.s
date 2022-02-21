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
	.file	"startup.c"
	.text
	.align	2
	.global	Default_Handler
	.arch armv4t
	.syntax unified
	.arm
	.fpu softvfp
	.type	Default_Handler, %function
Default_Handler:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	bl	Rest_Handler
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, lr}
	bx	lr
	.size	Default_Handler, .-Default_Handler
	.weak	Usage_Fault_Handler
	.set	Usage_Fault_Handler,Default_Handler
	.weak	Bus_Fault_Handler
	.set	Bus_Fault_Handler,Default_Handler
	.weak	MM_Fault_Handler
	.set	MM_Fault_Handler,Default_Handler
	.weak	Hard_Fault_Handler
	.set	Hard_Fault_Handler,Default_Handler
	.weak	NMI_Handler
	.set	NMI_Handler,Default_Handler
	.global	vectors
	.section	.vectors,"aw"
	.align	2
	.type	vectors, %object
	.size	vectors, 28
vectors:
	.word	_stack_top
	.word	Rest_Handler
	.word	NMI_Handler
	.word	Hard_Fault_Handler
	.word	MM_Fault_Handler
	.word	Bus_Fault_Handler
	.word	Usage_Fault_Handler
	.text
	.align	2
	.global	Rest_Handler
	.syntax unified
	.arm
	.fpu softvfp
	.type	Rest_Handler, %function
Rest_Handler:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #24
	ldr	r2, .L7
	ldr	r3, .L7+4
	sub	r3, r2, r3
	str	r3, [fp, #-24]
	ldr	r3, .L7+8
	str	r3, [fp, #-8]
	ldr	r3, .L7+4
	str	r3, [fp, #-12]
	mov	r3, #0
	str	r3, [fp, #-16]
	b	.L3
.L4:
	ldr	r2, [fp, #-8]
	add	r3, r2, #1
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-12]
	add	r1, r3, #1
	str	r1, [fp, #-12]
	ldrb	r2, [r2]	@ zero_extendqisi2
	strb	r2, [r3]
	ldr	r3, [fp, #-16]
	add	r3, r3, #1
	str	r3, [fp, #-16]
.L3:
	ldr	r3, [fp, #-16]
	ldr	r2, [fp, #-24]
	cmp	r2, r3
	bhi	.L4
	ldr	r2, .L7+12
	ldr	r3, .L7+16
	sub	r3, r2, r3
	str	r3, [fp, #-28]
	ldr	r3, .L7+16
	str	r3, [fp, #-12]
	mov	r3, #0
	str	r3, [fp, #-20]
	b	.L5
.L6:
	ldr	r3, [fp, #-12]
	add	r3, r3, #1
	str	r3, [fp, #-12]
	ldr	r3, [fp, #-20]
	add	r3, r3, #1
	str	r3, [fp, #-20]
.L5:
	ldr	r3, [fp, #-20]
	ldr	r2, [fp, #-28]
	cmp	r2, r3
	bhi	.L6
	bl	main
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, lr}
	bx	lr
.L8:
	.align	2
.L7:
	.word	_E_DATA
	.word	_S_DATA
	.word	_E_text
	.word	_E_bss
	.word	_S_bss
	.size	Rest_Handler, .-Rest_Handler
	.ident	"GCC: (GNU Tools for STM32 9-2020-q2-update.20201001-1621) 9.3.1 20200408 (release)"
