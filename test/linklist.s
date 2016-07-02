	.text
	.file	"./test/linklist.ll"
	.globl	f
	.align	16, 0x90
	.type	f,@function
f:                                      # @f
	.cfi_startproc
# BB#0:                                 # %entry
	movq	%rdi, -8(%rsp)
	movq	%rdi, -16(%rsp)
	retq
.Ltmp0:
	.size	f, .Ltmp0-f
	.cfi_endproc

	.globl	g
	.align	16, 0x90
	.type	g,@function
g:                                      # @g
	.cfi_startproc
# BB#0:                                 # %entry
	movq	%rdi, -8(%rsp)
	retq
.Ltmp1:
	.size	g, .Ltmp1-g
	.cfi_endproc

	.globl	h
	.align	16, 0x90
	.type	h,@function
h:                                      # @h
	.cfi_startproc
# BB#0:                                 # %entry
	movq	%rdi, -8(%rsp)
	retq
.Ltmp2:
	.size	h, .Ltmp2-h
	.cfi_endproc

	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# BB#0:                                 # %entry
	subq	$24, %rsp
.Ltmp3:
	.cfi_def_cfa_offset 32
	movq	16(%rsp), %rdi
	callq	f
	movq	8(%rsp), %rdi
	callq	h
	xorl	%eax, %eax
	addq	$24, %rsp
	retq
.Ltmp4:
	.size	main, .Ltmp4-main
	.cfi_endproc


	.section	".note.GNU-stack","",@progbits
