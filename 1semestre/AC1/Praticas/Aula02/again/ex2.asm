	.data
	.text
	.globl main
main: 	li $t0, 0x12345678
	
	sll $t2, $t0, 1
	srl $t3, $t0, 1
	sra $t4, $t0, 1
	
	or $a0, $0, $t2
	li $v0, 35
	syscall
	
	or $a0, $0, $t3
	li $v0, 35
	syscall
	
	or $a0, $0, $t4
	li $v0, 35
	syscall
	
	jr $ra