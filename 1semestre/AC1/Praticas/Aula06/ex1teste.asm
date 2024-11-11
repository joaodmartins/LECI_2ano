# Mapa de registos
# 
# i: $t0

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
	
main: 	li $t0, 0
	
for: 	bge $t0, SIZE, endfor

	la $t1, array		# $t1 = &array[0]
	sll $t2, $t0, 2		# $t2 = i * 4
	addu $t2, $t1, $t2	# $t1 = &array[i]
	lw $t3, 0($t2)		# $t2 = array[i]
	
	li $v0, print_string
	move $a0, $t3
	syscall
	
	li $v0, print_char
	li $a0, '\n'
	syscall
	
	addi $t0, $t0, 1
	
	j for
	
endfor: jr $ra	
	
	
