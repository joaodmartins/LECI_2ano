# Mapa de registos
#
# res:		$t0
# i: 		$t1
# mdor:		$t2
# mdo:		$t3

	.data
	
str1: 	.asciiz "Introduz dois numeros: "
str2: 	.asciiz "Resultado: "

	.eqv print_string, 4
	.eqv read_int, 5
	.eqv print_int10, 1
	
	.text
	.globl main
	
main: 	li $v0, print_string
	la $a0, str1
	syscall
	
	li $v0, read_int
	syscall
	andi $t2, $v0, 0x0F
	
	li $v0, read_int
	syscall
	andi $t3, $v0, 0x0F
	
	li $t0, 0
	li $t1, 0
	
while:  beq $t2, $zero, endw
	bge $t1, 4, endw
	
if: 	andi $t4, $t2, 0x00000001
	beq $t4, $zero, endif
	
	add $t0, $t0, $t3
	
endif: 	sll $t3, $t3, 1
	srl $t2, $t2, 1
	
	addi $t1, $t1, 1
	
	j while
	
endw: 	li $v0, print_string
	la $a0, str2
	syscall
	
	li $v0, print_int10
	move $a0, $t0
	syscall
	
	jr $ra
	