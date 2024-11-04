# Mapa de registos
# 
# p: 		$t1
# pultimo:	$t2

	.data
	.eqv SIZE, 3
	.eqv print_string, 4
	.eqv print_char, 11
	
str1: 	.asciiz "Array"
str2: 	.asciiz "de"
str3: 	.asciiz "ponteiros"
array: 	.word str1, str2, str3

	.text
	.globl main
	
main: 	la $t1, array
	
	li $t0, SIZE
	sll $t0, $t0, 2
	addu $t2, $t1, $t0
	
for: 	bge $t1, $t2, endfor

	li $v0, print_string
	lw $a0, 0($t1)
	syscall
	
	li $v0, print_char
	li $a0, '\n'
	syscall
	
	addi $t1, $t1, 4
	
	j for
	
endfor: jr $ra