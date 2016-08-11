	.file	"test1.c"
	.section	.rodata
.LC0:
	.string	"%d\n"
	.text
.globl fun
	.type	fun, @function
fun:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	$0, -12(%ebp)
	jmp	.L2
.L3:
	movl	$.LC0, %eax
	movl	-12(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	printf
	addl	$1, -12(%ebp)
.L2:
	cmpl	$99, -12(%ebp)
	jle	.L3
	leave
	ret
	.size	fun, .-fun
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$32, %esp
	movl	$0, 24(%esp)
	movl	$0, 28(%esp)
	jmp	.L6
.L7:
	movl	28(%esp), %eax
	addl	%eax, 24(%esp)
	addl	$1, 28(%esp)
.L6:
	cmpl	$100, 28(%esp)
	jle	.L7
	movl	$.LC0, %eax
	movl	24(%esp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	printf
	call	fun
	nop
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 4.4.7 20120313 (Red Hat 4.4.7-4)"
	.section	.note.GNU-stack,"",@progbits
