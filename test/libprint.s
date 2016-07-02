	.file	"libprint.c"
	.globl	globalint
	.bss
	.align 4
	.type	globalint, @object
	.size	globalint, 4
globalint:
	.zero	4
	.globl	globalfloat
	.align 8
	.type	globalfloat, @object
	.size	globalfloat, 8
globalfloat:
	.zero	8
	.section	.rodata
.LC0:
	.string	"globalint : %d \n"
	.text
	.globl	printint
	.type	printint, @function
printint:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	globalint(%rip), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	printint, .-printint
	.section	.rodata
.LC1:
	.string	"globalfloat : %f \n"
	.text
	.globl	printfloat
	.type	printfloat, @function
printfloat:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	globalfloat(%rip), %rax
	movq	%rax, -8(%rbp)
	movsd	-8(%rbp), %xmm0
	movl	$.LC1, %edi
	movl	$1, %eax
	call	printf
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	printfloat, .-printfloat
	.section	.rodata
.LC2:
	.string	"num : %d \n"
	.text
	.globl	printa
	.type	printa, @function
printa:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	printa, .-printa
	.ident	"GCC: (Ubuntu 5.2.1-22ubuntu2) 5.2.1 20151010"
	.section	.note.GNU-stack,"",@progbits
