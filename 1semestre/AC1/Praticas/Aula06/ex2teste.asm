# Mapa de registos
#
# p:		$t0	
# pultimo: 	$t1

	.data
	.eqv SIZE, 3
	.eqv print_string, 4 
	.eqv print_char, 11
	
str1:	.asciiz "Array" 
str2:	.asciiz "de"
str3: 	.asciiz "ponteiros"
array: 	.word str1, str2, str3

	.text
	.globl main
	
main: 	la $t0, array 		# p = &array[0]
	li $t2, SIZE 		# $t1 = SIZE
	sll $t2, $t2, 2 	# $t1 = SIZE * 4
	addu $t1, $t0, $t2 	# pultimo = &array[SIZE]
	
for: 	bge $t0, $t1, endfor
	
	lw $a0, 0($t0)
	
	li $v0, print_string
	syscall
	
	li $v0, print_char
	li $a0, '\n'
	syscall
	
	addi $t0, $t0, 4
	
	j for
	
endfor: jr $ra
	