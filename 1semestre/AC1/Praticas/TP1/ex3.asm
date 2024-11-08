# Mapa de registos
#
# n: $t0
# c: $t1
# k: $t2
# p: $t3

	.data
	.eqv CHAR_BIN_LEN, 33
	.eqv MS_BIT, 31
	.eqv print_string, 4
	.eqv read_int, 5
	
bin_nbr:	.space CHAR_BIN_LEN
	
str1:	.asciiz "Inteiro em decimal: "
str2: 	.asciiz "Em binario e: "
	
	.text
	.globl main
	
main: 	li $v0, print_string
	la $a0, str1
	syscall
	
	li $v0, read_int
	syscall
	move $t0, $v0
	
	li $v0, print_string
	la $a0, str2
	syscall
	
	la $t3, bin_nbr
	li $t1, MS_BIT
	
for: 	bltz $t1, endfor

	srlv $t2, $t0, $t1

	andi $t2, $t2, 1
	
	beq $t2, $zero, iszero
	
	li $t2, '1'
	sb $t2, 0($t3)
	
	j next

iszero: li $t2, '0'
	sb $t2, 0($t3)
	
next: 	addiu $t3, $t3, 1
	addi $t1, $t1, -1
	
	j for
	
endfor: sb $0, 0($t3)
	
	li $v0, print_string
	la $a0, bin_nbr
	syscall
	
	jr $ra
	