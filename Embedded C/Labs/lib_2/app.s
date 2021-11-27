
app.o:     file format elf32-littlearm


Disassembly of section .text:

00000000 <main>:
   0:	e92d4800 	push	{fp, lr}
   4:	e28db004 	add	fp, sp, #4
   8:	e59f000c 	ldr	r0, [pc, #12]	; 1c <main+0x1c>
   c:	ebfffffe 	bl	0 <UART_send>
  10:	e59f0008 	ldr	r0, [pc, #8]	; 20 <main+0x20>
  14:	ebfffffe 	bl	0 <uart2_send>
  18:	e8bd8800 	pop	{fp, pc}
	...

Disassembly of section .data:

00000000 <buffer>:
   0:	2d756f59 	ldclcs	15, cr6, [r5, #-356]!	; 0xfffffe9c
   4:	2d6e6143 	stfcse	f6, [lr, #-268]!	; 0xfffffef4
   8:	692d6f64 	pushvs	{r2, r5, r6, r8, r9, sl, fp, sp, lr}
   c:	00000074 	andeq	r0, r0, r4, ror r0
	...

00000020 <buffer2>:
  20:	61726159 	cmnvs	r2, r9, asr r1
  24:	61532062 	cmpvs	r3, r2, rrx
  28:	696e6469 	stmdbvs	lr!, {r0, r3, r5, r6, sl, sp, lr}^
  2c:	00000000 	andeq	r0, r0, r0

Disassembly of section .rodata:

00000000 <buffer3>:
   0:	6d656441 	cfstrdvs	mvd6, [r5, #-260]!	; 0xfffffefc
   4:	72614d20 	rsbvc	r4, r1, #32, 26	; 0x800
   8:	6f676e61 	svcvs	0x00676e61

Disassembly of section .comment:

00000000 <.comment>:
   0:	43434700 	movtmi	r4, #14080	; 0x3700
   4:	4728203a 			; <UNDEFINED> instruction: 0x4728203a
   8:	2029554e 	eorcs	r5, r9, lr, asr #10
   c:	2e372e34 	mrccs	14, 1, r2, cr7, cr4, {1}
  10:	Address 0x00000010 is out of bounds.


Disassembly of section .ARM.attributes:

00000000 <.ARM.attributes>:
   0:	00003141 	andeq	r3, r0, r1, asr #2
   4:	61656100 	cmnvs	r5, r0, lsl #2
   8:	01006962 	tsteq	r0, r2, ror #18
   c:	00000027 	andeq	r0, r0, r7, lsr #32
  10:	4d524105 	ldfmie	f4, [r2, #-20]	; 0xffffffec
  14:	45363239 	ldrmi	r3, [r6, #-569]!	; 0x239
  18:	00532d4a 	subseq	r2, r3, sl, asr #26
  1c:	01080506 	tsteq	r8, r6, lsl #10
  20:	04120109 	ldreq	r0, [r2], #-265	; 0x109
  24:	01150114 	tsteq	r5, r4, lsl r1
  28:	01180317 	tsteq	r8, r7, lsl r3
  2c:	011a0119 	tsteq	sl, r9, lsl r1
  30:	Address 0x00000030 is out of bounds.

