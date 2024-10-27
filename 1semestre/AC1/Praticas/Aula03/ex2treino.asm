# Mapa de registos:
# 
# value: 	$t0
# bit:		$t1
# i: 		$t2

	.data

str1:	.asciiz "Introduza um numero: "
str2:	.asciiz "\nO valor em binário e': "
	
	.eqv 	print_string, 4
	.eqv 	read_int, 5
	.eqv	print_char, 11
	
	.text
	.globl main
	
main:	li $v0, print_string
	la $a0, str1
	syscall
	
	li $v0, read_int
	syscall
	move $t0, $v0
	
	li $v0, print_string
	la $a0, str2
	syscall
	
	li $t2, 0
	
for: 	bge $t2, 32, endfor
	
	rem $t4, $t2, 4
	bne $t4, $zero, nospace
	
	li $v0, print_char
	li $a0, ' '
	syscall
	
nospace:
	li $t3, 0x80000000
	
	and $t1, $t0, $t3
	
if:	beq $t1, $zero, else
	
	li $v0, print_char
	li $a0, '1'
	syscall 
	
	j endif
	
else: 	li $v0, print_char
	li $a0, '0'
	syscall 
	
endif: 	sll $t0, $t0, 1
	
	addi $t2, $t2, 1
	
	j for

endfor: jr $ra