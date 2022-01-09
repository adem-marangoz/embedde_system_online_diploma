	.file	"Pressure_sensor_driver.c"
	.comm	_Pressure_state, 4, 2
	.globl	_Pressure_P_fun
	.data
	.align 4
_Pressure_P_fun:
	.long	_Pr_Reading_and_sending
	.comm	_Pressure_Value, 4, 2
	.section .rdata,"dr"
LC0:
	.ascii "\12---- Pressure_Init ----\0"
	.text
	.globl	_init_Pressure
	.def	_init_Pressure;	.scl	2;	.type	32;	.endef
_init_Pressure:
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
	.ascii "\12Pressure_sensor_driver:---> Reading Pressure value = %d \0"
	.text
	.globl	_Pr_Reading_and_sending
	.def	_Pr_Reading_and_sending;	.scl	2;	.type	32;	.endef
_Pr_Reading_and_sending:
LFB11:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	$1, 8(%esp)
	movl	$25, 4(%esp)
	movl	$15, (%esp)
	call	_Get_Pressure_random
	movl	%eax, _Pressure_Value
	movl	__imp___iob, %eax
	movl	%eax, (%esp)
	call	_fflush
	movl	__imp___iob, %eax
	addl	$32, %eax
	movl	%eax, (%esp)
	call	_fflush
	movl	_Pressure_Value, %eax
	movl	%eax, 4(%esp)
	movl	$LC1, (%esp)
	call	_printf
	movl	__imp___iob, %eax
	movl	%eax, (%esp)
	call	_fflush
	movl	__imp___iob, %eax
	addl	$32, %eax
	movl	%eax, (%esp)
	call	_fflush
	movl	_Pressure_Value, %eax
	movl	%eax, (%esp)
	call	_Send_pressure_value
	movl	$_Pr_Waiting, _Pressure_P_fun
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
	.ascii "\12Pressure_sensor_driver:---> waiting Pressure  value \0"
	.align 4
LC3:
	.ascii "Pressure_sensor_driver:---> Ending wait for pressure\0"
	.text
	.globl	_Pr_Waiting
	.def	_Pr_Waiting;	.scl	2;	.type	32;	.endef
_Pr_Waiting:
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
	movl	$LC2, (%esp)
	call	_puts
	movl	__imp___iob, %eax
	movl	%eax, (%esp)
	call	_fflush
	movl	__imp___iob, %eax
	addl	$32, %eax
	movl	%eax, (%esp)
	call	_fflush
	movl	_counter.1909, %eax
	addl	$1, %eax
	movl	%eax, _counter.1909
	movl	_counter.1909, %eax
	cmpl	$5, %eax
	jne	L5
	movl	$0, _counter.1909
	movl	$_Pr_Reading_and_sending, _Pressure_P_fun
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
L5:
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE12:
	.globl	_Get_Pressure_random
	.def	_Get_Pressure_random;	.scl	2;	.type	32;	.endef
_Get_Pressure_random:
LFB13:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	$0, -12(%ebp)
	movl	-12(%ebp), %eax
	cmpl	16(%ebp), %eax
	jge	L7
	call	_rand
	movl	%eax, %edx
	movl	12(%ebp), %eax
	subl	8(%ebp), %eax
	leal	1(%eax), %ecx
	movl	%edx, %eax
	cltd
	idivl	%ecx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
	jmp	L8
L7:
	movl	$0, %eax
L8:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE13:
.lcomm _counter.1909,4,4
	.ident	"GCC: (MinGW.org GCC-6.3.0-1) 6.3.0"
	.def	_fflush;	.scl	2;	.type	32;	.endef
	.def	_puts;	.scl	2;	.type	32;	.endef
	.def	_printf;	.scl	2;	.type	32;	.endef
	.def	_Send_pressure_value;	.scl	2;	.type	32;	.endef
	.def	_rand;	.scl	2;	.type	32;	.endef
