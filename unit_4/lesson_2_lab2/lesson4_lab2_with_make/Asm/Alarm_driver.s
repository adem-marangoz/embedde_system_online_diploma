	.file	"Alarm_driver.c"
	.comm	_Prev_Alarm_state, 4, 2
	.comm	_Curr_Alarm_state, 4, 2
	.globl	_Alarm_p_fun
	.data
	.align 4
_Alarm_p_fun:
	.long	_Al_Alarm_Off
	.section .rdata,"dr"
LC0:
	.ascii "--- Alarm Init ----\0"
	.text
	.globl	_Alarm_init
	.def	_Alarm_init;	.scl	2;	.type	32;	.endef
_Alarm_init:
LFB10:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	$0, _Prev_Alarm_state
	movl	$0, _Curr_Alarm_state
	movl	$_Al_Alarm_Off, _Alarm_p_fun
	movl	__imp___iob, %eax
	movl	%eax, (%esp)
	call	_fflush
	movl	__imp___iob, %eax
	addl	$32, %eax
	movl	%eax, (%esp)
	call	_fflush
	movl	$LC0, (%esp)
	call	_puts
	movl	__imp___iob, %eax
	movl	%eax, (%esp)
	call	_fflush
	movl	__imp___iob, %eax
	addl	$32, %eax
	movl	%eax, (%esp)
	call	_fflush
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE10:
	.section .rdata,"dr"
	.align 4
LC1:
	.ascii "\12Alarm_driver:==== Led is Off ====\0"
	.text
	.globl	_Al_Alarm_Off
	.def	_Al_Alarm_Off;	.scl	2;	.type	32;	.endef
_Al_Alarm_Off:
LFB11:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	$0, _Prev_Alarm_state
	movl	$0, _Curr_Alarm_state
	movl	__imp___iob, %eax
	movl	%eax, (%esp)
	call	_fflush
	movl	__imp___iob, %eax
	addl	$32, %eax
	movl	%eax, (%esp)
	call	_fflush
	movl	$LC1, (%esp)
	call	_puts
	movl	__imp___iob, %eax
	movl	%eax, (%esp)
	call	_fflush
	movl	__imp___iob, %eax
	addl	$32, %eax
	movl	%eax, (%esp)
	call	_fflush
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE11:
	.section .rdata,"dr"
	.align 4
LC2:
	.ascii "\12Alarm_driver:==== Led is On ====\0"
	.text
	.globl	_Al_Alarm_On
	.def	_Al_Alarm_On;	.scl	2;	.type	32;	.endef
_Al_Alarm_On:
LFB12:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	$1, _Prev_Alarm_state
	movl	$1, _Curr_Alarm_state
	movl	__imp___iob, %eax
	movl	%eax, (%esp)
	call	_fflush
	movl	__imp___iob, %eax
	addl	$32, %eax
	movl	%eax, (%esp)
	call	_fflush
	movl	$LC2, (%esp)
	call	_puts
	movl	__imp___iob, %eax
	movl	%eax, (%esp)
	call	_fflush
	movl	__imp___iob, %eax
	addl	$32, %eax
	movl	%eax, (%esp)
	call	_fflush
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE12:
	.globl	_Alarm_on_off_fun
	.def	_Alarm_on_off_fun;	.scl	2;	.type	32;	.endef
_Alarm_on_off_fun:
LFB13:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	$0, _Prev_Alarm_state
	movl	$1, _Curr_Alarm_state
	cmpl	$0, 8(%ebp)
	jne	L5
	movl	$_Al_Alarm_Off, _Alarm_p_fun
	jmp	L7
L5:
	movl	$_Al_Alarm_On, _Alarm_p_fun
L7:
	nop
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE13:
	.ident	"GCC: (MinGW.org GCC-6.3.0-1) 6.3.0"
	.def	_fflush;	.scl	2;	.type	32;	.endef
	.def	_puts;	.scl	2;	.type	32;	.endef
