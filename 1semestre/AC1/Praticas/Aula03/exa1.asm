# Mapa de registos:
#
# gray:		$t0
# bin:		$t1
# mask: 	$t2

	.data

str1:	.asciiz "Introduza um número: "
str2:	.asciiz	"\nValor em código de Gray: "
str3:	.asciiz "\nValor em binário: "
	
	.eqv print_string, 4
	.eqv read_int, 5
	.eqv print_int16, 34
	
	.text
	.globl main
	
main: 	li $v0, print_string
	la $a0, str1
	syscall
	
	li $v0, read_int
	syscall
	move $t0, $v0
	
	srl $t2, $t0, 1
	move $t1, $t0
	
while: 	beq $t2, $zero, endw

	xor $t1, $t1, $t2
	srl $t2, $t2, 1
	
endw:	li $v0, print_string
	la $a0, str2
	syscall
	
	li $v0, print_int16
	move $a0, $t0
	syscall
	
	li $v0, print_string
	la $a0, str3
	syscall
	
	li $v0, print_int16
	move $a0, $t1
	syscall
	
	jr $ra
	
	
