	.file	"main.c"
	.comm	_Main_Al_State, 4, 2
	.comm	_Pressure_state, 4, 2
	.comm	_Timer_state, 4, 2
	.text
	.globl	_setup
	.def	_setup;	.scl	2;	.type	32;	.endef
_setup:
LFB10:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	call	_init_Pressure
	call	_Alarm_init
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE10:
	.def	___main;	.scl	2;	.type	32;	.endef
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB11:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$16, %esp
	call	___main
	call	_setup
	movl	$50, 12(%esp)
	jmp	L3
L4:
	movl	12(%esp), %eax
	subl	$1, %eax
	movl	%eax, 12(%esp)
	movl	_Pressure_P_fun, %eax
	call	*%eax
	movl	_Main_p_fun, %eax
	call	*%eax
	movl	_Timer_p_fun, %eax
	call	*%eax
	movl	_Prev_Alarm_state, %edx
	movl	_Curr_Alarm_state, %eax
	cmpl	%eax, %edx
	je	L3
	movl	_Alarm_p_fun, %eax
	call	*%eax
L3:
	movl	12(%esp), %eax
	testl	%eax, %eax
	jne	L4
	movl	$0, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE11:
	.ident	"GCC: (MinGW.org GCC-6.3.0-1) 6.3.0"
	.def	_init_Pressure;	.scl	2;	.type	32;	.endef
	.def	_Alarm_init;	.scl	2;	.type	32;	.endef
