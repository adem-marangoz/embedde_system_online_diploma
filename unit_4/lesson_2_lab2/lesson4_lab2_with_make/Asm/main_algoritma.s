	.file	"main_algoritma.c"
	.comm	_Main_Al_State, 4, 2
	.comm	_Pressure_Value, 4, 2
	.globl	_Threshold
	.data
	.align 4
_Threshold:
	.long	20
	.globl	_Main_p_fun
	.align 4
_Main_p_fun:
	.long	_Algoritma_Data_waiting
	.text
	.globl	_Algoritma_Data_waiting
	.def	_Algoritma_Data_waiting;	.scl	2;	.type	32;	.endef
_Algoritma_Data_waiting:
LFB10:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	nop
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE10:
	.section .rdata,"dr"
	.align 4
LC0:
	.ascii "\12main_algoritma:---> Calculated Data \0"
	.align 4
LC1:
	.ascii "main_algoritma:---> Pressure High Detected\0"
	.text
	.globl	_Algoritma_Calculate_data
	.def	_Algoritma_Calculate_data;	.scl	2;	.type	32;	.endef
_Algoritma_Calculate_data:
LFB11:
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
	movl	_Pressure_Value, %edx
	movl	_Threshold, %eax
	cmpl	%eax, %edx
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
	call	_Timer_starting
L3:
	movl	$_Algoritma_Data_waiting, _Main_p_fun
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
	.ascii "\12main_algoritma:---> Data Received \0"
	.text
	.globl	_Send_pressure_value
	.def	_Send_pressure_value;	.scl	2;	.type	32;	.endef
_Send_pressure_value:
LFB12:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	8(%ebp), %eax
	movl	%eax, _Pressure_Value
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
	movl	$_Algoritma_Calculate_data, _Main_p_fun
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE12:
	.ident	"GCC: (MinGW.org GCC-6.3.0-1) 6.3.0"
	.def	_fflush;	.scl	2;	.type	32;	.endef
	.def	_puts;	.scl	2;	.type	32;	.endef
	.def	_Timer_starting;	.scl	2;	.type	32;	.endef
	.def	_printf;	.scl	2;	.type	32;	.endef
