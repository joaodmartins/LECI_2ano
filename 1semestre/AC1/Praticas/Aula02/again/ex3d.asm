	.data
str1:	.asciiz "Introduza 2 numeros "
str2:	.asciiz "A soma dos dois numeros e': "
	.eqv 	print_string, 4
	.eqv 	print_int10, 1
	.eqv	read_int, 5
	
	.text
	.globl main
main:	la $a0, str1
	ori $v0, $0, print_string
	syscall
	
	ori $v0, $0, read_int
	syscall
	or $t0, $0, $v0
	
	ori $v0, $0, read_int
	syscall
	or $t1, $0, $v0
	
	la $a0, str2
	ori $v0, $0, print_string
	syscall

	add $t2, $t0, $t1
	
	or $a0, $0, $t2
	ori $v0, $0, print_int10
	syscall
	
	jr $ra