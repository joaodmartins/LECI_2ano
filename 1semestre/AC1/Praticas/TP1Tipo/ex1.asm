# Mapa de registos
#
# val:	$t0
# n: 	$t1
# min:	$t2
# max:	$t3

	.data
	.eqv print_string, 4
	.eqv read_int, 5
	.eqv print_int10, 1
	.eqv print_char, 11
	
str1: 	.asciiz "Digite até 20 inteiros (zero para terminar): "
str2: 	.asciiz "Maximo/minimo sao:"
	
	.text 
	.globl main
	
main: 	li $v0, print_string
	la $a0, str1
	syscall
	
	li $t1, 0
	
	li $t2, 0x7FFFFFFF
	li $t3, 0x80000000
	
do: 	li $v0, read_int
	syscall
	move $t0, $v0
	
if1: 	beq $t0, $zero, endif1
	
if2: 	ble $t0, $t3, if3
	
	move $t3, $t0
	
if3: 	bge $t0, $t3, endif1
	
	move $t2, $t0
	
endif1:	addi $t1, $t1, 1

while:	bge $t1, 20, enddw
	
	beq $t0, $zero, enddw
	
	j do
	
enddw: 	li $v0, print_string
	la $a0, str2
	syscall
	
	li $v0, print_int10
	move $a0, $t3
	syscall
	
	li $v0, print_string
	li $a0, ':'
	syscall
	
	li $v0, print_int10
	move $a0, $t2
	syscall
	
	jr $ra