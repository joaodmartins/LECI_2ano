# Mapa de registos
#
# p: 	$t0 
# *p:	$t1

	.data
	.eqv SIZE, 20
	.eqv print_string, 4
	.eqv read_string, 8
	
str: 	.space 21
str1:	.asciiz "Introduza uma string: "

	.text
	.globl main
	
main:	li $v0, print_string
	la $a0, str1
	syscall
	
	li $v0, read_string
	la $a0, str
	li $a1, SIZE
	syscall
	
	la $t0, str
	
while: 	lb $t1, 0($t0)
	
	beq $t1, '\0', endw
	
	li $t2, 'a'
	li $t3, 'A'
	
	sub $t1, $t1, $t2
	add $t1, $t1, $t3
	
	sb $t1, 0($t0)
	
	addi $t0, $t0, 1
	
	j while
	
endw: 	li $v0, print_string
	la $a0, str
	syscall
	
	jr $ra 

