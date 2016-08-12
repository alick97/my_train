	.file	"test.c"
	.text
.globl fun
	.type	fun, @function
fun:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$0, -8(%ebp)
	movl	$0, -4(%ebp)
	jmp	.L2
.L3:
	movl	-8(%ebp), %eax
	addl	%eax, -4(%ebp)
	addl	$1, -8(%ebp)
.L2:
	cmpl	$99, -8(%ebp)
	jle	.L3
	leave
	ret
	.size	fun, .-fun
	.section	.rodata
.LC0:
	.string	"hello word"
	.text
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$16, %esp
	movl	$.LC0, %eax
	movl	%eax, (%esp)
	call	printf
	call	fun
	movl	$.LC0, %eax
	movl	%eax, (%esp)
	call	printf
	movl	$0, %eax
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 4.4.7 20120313 (Red Hat 4.4.7-4)"
	.section	.note.GNU-stack,"",@progbits
