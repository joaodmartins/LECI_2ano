# Mapa de registos
# 
# i:		$t0
# lista:	$t1
# lista + i:	$t2

	.data
	.align 2
	.eqv SIZE, 5
str: 	.asciiz "\nIntroduza um numero: "
lista: 	.space 20
	
	.text 
	.globl main
	
main: 	li $t0, 0
	
while: 	bge $t0, SIZE, endw
	
	li $v0, 4
	la $a0, str
	syscall
	
	li $v0, 5
	syscall
	
	la $t1, lista
	sll $t2, $t0, 2
	addu $t2, $t1, $t2
	
	sw $v0, 0($t2)
	
	addi $t0, $t0, 1
	
	j while
	
endw: 	
	jr $ra