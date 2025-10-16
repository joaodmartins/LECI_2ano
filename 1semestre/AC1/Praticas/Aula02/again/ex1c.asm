	.data
	.text
	.globl main
main:	ori $t0, $0, 0x0F1E
	nor $t1, $0, $t0
	
	or $a0, $0, $t1
	ori $v0, $0, 34
	syscall
	
	jr $ra