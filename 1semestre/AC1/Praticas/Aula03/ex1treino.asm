# Mapa de registos
#
# soma:		$t0
# value:	$t1
# i:		$t2

	.data

str1: 	.asciiz "Introduz um numero: "
str2:	.asciiz "Valor ignorado\n"
str3: 	.asciiz "A soma dos positivos e': "	
	.eqv read_int, 5
	.eqv print_string, 4
	.eqv print_int10, 1
 	
	.text
	.globl main
main: 	li $t0, 0
	li $t2, 0
	
for: 	bge $t2, 5, endfor
	
	li $v0, print_string
	la $a0, str1
	syscall
	
	li $v0, read_int
	syscall
	move $t1, $v0
	
	addi $t2, $t2, 1
	
if: 	blez $t2, else
	
	add $t0, $t0, $t1
	
	j for
	
else:	li $v0, print_string
	la $a0, str2
	syscall
	
	j for
	
endfor:	li $v0, print_string
	la $a0, str3
	syscall
	
	li $v0, print_int10
	move $a0, $t0
	syscall
	
	jr $ra

	
