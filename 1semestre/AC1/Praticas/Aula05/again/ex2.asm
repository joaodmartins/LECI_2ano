# Mapa de registos
# p:		$t0
# *p:		$t1 (Registo temporário para guardar o valor armazenado em memória)
# lista + SIZE:	$t2

	.data
	.eqv SIZE, 10
	.eqv print_string, 4
	.eqv print_int10, 1
	
str1: 	.asciiz "\nConteudo do array:\n"
str2:	.asciiz "; "
lista:	.word 8, -4, 3, 5, 124, -15, 87, 9, 27, 15	# a diretiva ".word" alinha num endereço multiplo de 4
	
	.text
	.globl main

main:	la $a0, str1
	li $v0, print_string
	syscall				# print("\nConteudo do array:\n")
	
	la $t0, lista			# p = lista
	li $t3, SIZE			# $t3 = SIZE
	sll $t3, $t3, 2			# $t3 = SIZE * 4
	addu $t2, $t0, $t3		# $t2 = lista + SIZE
	
while:	bgeu $t0, $t2, endw		# while(p < lista+SIZE) {
	
	lw $t1, 0($t0)			# $t1 = *p
	
	move $a0, $t1
	li $v0, print_int10		
	syscall				# print_int10( *p )
	
	la $a0, str2			
	li $v0, print_string
	syscall				# print_string("; ")
	
	addiu $t0, $t0, 4
	
	j while

endw:	jr $ra