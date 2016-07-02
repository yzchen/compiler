	.text
	.file	"./test/heapsort.ll"
	.globl	HeapAdjust
	.align	16, 0x90
	.type	HeapAdjust,@function
HeapAdjust:                             # @HeapAdjust
	.cfi_startproc
# BB#0:                                 # %entry
	movl	%edi, -4(%rsp)
	movl	%esi, -8(%rsp)
	movslq	-4(%rsp), %rax
	movl	H(,%rax,4), %eax
	movl	%eax, -12(%rsp)
	movl	-4(%rsp), %eax
	leal	1(%rax,%rax), %eax
	movl	%eax, -16(%rsp)
	jmp	.LBB0_1
	.align	16, 0x90
.LBB0_6:                                # %ifcont32
                                        #   in Loop: Header=BB0_1 Depth=1
	movslq	-16(%rsp), %rax
	movl	H(,%rax,4), %eax
	movslq	-4(%rsp), %rcx
	movl	%eax, H(,%rcx,4)
	movl	-16(%rsp), %eax
	movl	%eax, -4(%rsp)
	leal	1(%rax,%rax), %eax
	movl	%eax, -16(%rsp)
	movl	-12(%rsp), %eax
	movslq	-4(%rsp), %rcx
	movl	%eax, H(,%rcx,4)
.LBB0_1:                                # %whilecond
                                        # =>This Inner Loop Header: Depth=1
	movl	-16(%rsp), %eax
	cmpl	-8(%rsp), %eax
	jge	.LBB0_7
# BB#2:                                 # %whileloop
                                        #   in Loop: Header=BB0_1 Depth=1
	movl	-16(%rsp), %eax
	incl	%eax
	cmpl	-8(%rsp), %eax
	jge	.LBB0_5
# BB#3:                                 # %then
                                        #   in Loop: Header=BB0_1 Depth=1
	movslq	-16(%rsp), %rax
	movl	H(,%rax,4), %ecx
	leal	1(%rax), %eax
	cltq
	cmpl	H(,%rax,4), %ecx
	jge	.LBB0_5
# BB#4:                                 # %then15
                                        #   in Loop: Header=BB0_1 Depth=1
	incl	-16(%rsp)
.LBB0_5:                                # %ifcont19
                                        #   in Loop: Header=BB0_1 Depth=1
	movslq	-4(%rsp), %rax
	movl	H(,%rax,4), %eax
	movl	%eax, -20(%rsp)
	movslq	-16(%rsp), %rcx
	cmpl	H(,%rcx,4), %eax
	jl	.LBB0_6
.LBB0_7:                                # %whilet
	retq
.Ltmp0:
	.size	HeapAdjust, .Ltmp0-HeapAdjust
	.cfi_endproc

	.globl	BuildingHeap
	.align	16, 0x90
	.type	BuildingHeap,@function
BuildingHeap:                           # @BuildingHeap
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rax
.Ltmp1:
	.cfi_def_cfa_offset 16
                                        # kill: EDI<def> EDI<kill> RDI<def>
	movl	%edi, 4(%rsp)
	leal	-1(%rdi), %eax
	shrl	$31, %eax
	leal	-1(%rdi,%rax), %eax
	sarl	%eax
	movl	%eax, (%rsp)
	jmp	.LBB1_1
	.align	16, 0x90
.LBB1_2:                                # %whileloop
                                        #   in Loop: Header=BB1_1 Depth=1
	movl	(%rsp), %edi
	movl	4(%rsp), %esi
	callq	HeapAdjust
	decl	(%rsp)
.LBB1_1:                                # %whilecond
                                        # =>This Inner Loop Header: Depth=1
	cmpl	$0, (%rsp)
	jns	.LBB1_2
# BB#3:                                 # %whilet
	popq	%rax
	retq
.Ltmp2:
	.size	BuildingHeap, .Ltmp2-BuildingHeap
	.cfi_endproc

	.globl	HeapSort
	.align	16, 0x90
	.type	HeapSort,@function
HeapSort:                               # @HeapSort
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp3:
	.cfi_def_cfa_offset 16
.Ltmp4:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp5:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	callq	BuildingHeap
	movl	-4(%rbp), %eax
	decl	%eax
	movl	%eax, -8(%rbp)
	jmp	.LBB2_1
	.align	16, 0x90
.LBB2_2:                                # %whileloop
                                        #   in Loop: Header=BB2_1 Depth=1
	movslq	-8(%rbp), %rax
	movl	H(,%rax,4), %eax
	movq	%rsp, %rcx
	leaq	-16(%rcx), %rdx
	movq	%rdx, %rsp
	movl	%eax, -16(%rcx)
	movl	H(%rip), %eax
	movslq	-8(%rbp), %rdx
	movl	%eax, H(,%rdx,4)
	movl	-16(%rcx), %eax
	movl	%eax, H(%rip)
	movl	-8(%rbp), %esi
	xorl	%edi, %edi
	callq	HeapAdjust
	decl	-8(%rbp)
.LBB2_1:                                # %whilecond
                                        # =>This Inner Loop Header: Depth=1
	cmpl	$0, -8(%rbp)
	jg	.LBB2_2
# BB#3:                                 # %whilet
	movq	%rbp, %rsp
	popq	%rbp
	retq
.Ltmp6:
	.size	HeapSort, .Ltmp6-HeapSort
	.cfi_endproc

	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rax
.Ltmp7:
	.cfi_def_cfa_offset 16
	movl	$10, %edi
	callq	HeapSort
	movl	$0, 4(%rsp)
	jmp	.LBB3_1
	.align	16, 0x90
.LBB3_2:                                # %whileloop
                                        #   in Loop: Header=BB3_1 Depth=1
	movslq	4(%rsp), %rax
	movl	H(,%rax,4), %edi
	movl	%edi, (%rsp)
	callq	printa
	incl	4(%rsp)
.LBB3_1:                                # %whilecond
                                        # =>This Inner Loop Header: Depth=1
	cmpl	$9, 4(%rsp)
	jle	.LBB3_2
# BB#3:                                 # %whilet
	xorl	%eax, %eax
	popq	%rdx
	retq
.Ltmp8:
	.size	main, .Ltmp8-main
	.cfi_endproc

	.type	H,@object               # @H
	.data
	.globl	H
	.align	16
H:
	.long	3                       # 0x3
	.long	1                       # 0x1
	.long	5                       # 0x5
	.long	7                       # 0x7
	.long	2                       # 0x2
	.long	4                       # 0x4
	.long	9                       # 0x9
	.long	6                       # 0x6
	.long	10                      # 0xa
	.long	8                       # 0x8
	.size	H, 40


	.section	".note.GNU-stack","",@progbits
