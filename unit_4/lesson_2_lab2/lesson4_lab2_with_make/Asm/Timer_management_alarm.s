	.file	"Timer_management_alarm.c"
	.comm	_Timer_state, 4, 2
.lcomm _counter1,4,4
	.globl	_Timer_p_fun
	.data
	.align 4
_Timer_p_fun:
	.long	_Timer_Timer_Alarm_Off
	.section .rdata,"dr"
	.align 4
LC0:
	.ascii "\12Timer_management_alarm:---> Timer is Off ---\0"
	.text
	.globl	_Timer_Timer_Alarm_Off
	.def	_Timer_Timer_Alarm_Off;	.scl	2;	.type	32;	.endef
_Timer_Timer_Alarm_Off:
LFB10:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	__imp___iob, %eax
	movl	%eax, (%esp)
	call	_fflush
	movl	__imp___iob, %eax
	addl	$32, %eax
	movl	%eax, (%esp)
	call	_fflush
	movl	$LC0, (%esp)
	call	_printf
	movl	__imp___iob, %eax
	movl	%eax, (%esp)
	call	_fflush
	movl	__imp___iob, %eax
	addl	$32, %eax
	movl	%eax, (%esp)
	call	_fflush
	movl	$0, (%esp)
	call	_Alarm_on_off_fun
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
	.ascii "Timer_management_alarm:---> Timer counting --->\0"
	.align 4
LC2:
	.ascii "\12Timer_management_alarm:---> Ending 60s for Timer \0"
	.text
	.globl	_Timer_Timer_Alarm_On
	.def	_Timer_Timer_Alarm_On;	.scl	2;	.type	32;	.endef
_Timer_Timer_Alarm_On:
LFB11:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	_counter1, %eax
	addl	$1, %eax
	movl	%eax, _counter1
	movl	_counter1, %eax
	cmpl	$1, %eax
	jbe	L3
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
L3:
	movl	_counter1, %eax
	cmpl	$8, %eax
	jne	L5
	movl	$0, _counter1
	movl	$_Timer_Timer_Alarm_Off, _Timer_p_fun
	movl	_Timer_p_fun, %eax
	call	*%eax
	movl	__imp___iob, %eax
	movl	%eax, (%esp)
	call	_fflush
	movl	__imp___iob, %eax
	addl	$32, %eax
	movl	%eax, (%esp)
	call	_fflush
	movl	$LC2, (%esp)
	call	_printf
	movl	__imp___iob, %eax
	movl	%eax, (%esp)
	call	_fflush
	movl	__imp___iob, %eax
	addl	$32, %eax
	movl	%eax, (%esp)
	call	_fflush
L5:
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE11:
	.section .rdata,"dr"
	.align 4
LC3:
	.ascii "Timer_management_alarm:---> Timer is On ---->\0"
	.text
	.globl	_Timer_starting
	.def	_Timer_starting;	.scl	2;	.type	32;	.endef
_Timer_starting:
LFB12:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	__imp___iob, %eax
	movl	%eax, (%esp)
	call	_fflush
	movl	__imp___iob, %eax
	addl	$32, %eax
	movl	%eax, (%esp)
	call	_fflush
	movl	$LC3, (%esp)
	call	_puts
	movl	__imp___iob, %eax
	movl	%eax, (%esp)
	call	_fflush
	movl	__imp___iob, %eax
	addl	$32, %eax
	movl	%eax, (%esp)
	call	_fflush
	movl	$_Timer_Timer_Alarm_On, _Timer_p_fun
	movl	$1, (%esp)
	call	_Alarm_on_off_fun
	movl	$0, _counter1
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE12:
	.ident	"GCC: (MinGW.org GCC-6.3.0-1) 6.3.0"
	.def	_fflush;	.scl	2;	.type	32;	.endef
	.def	_printf;	.scl	2;	.type	32;	.endef
	.def	_Alarm_on_off_fun;	.scl	2;	.type	32;	.endef
	.def	_puts;	.scl	2;	.type	32;	.endef
