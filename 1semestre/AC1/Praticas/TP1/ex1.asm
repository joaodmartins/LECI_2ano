# Mapa de registos
# 
# num1:	$t0
# num2:	$t1 
# res:	$t2 	
# erro:	$t3

	.data
	.eqv SIZE, 4
	.eqv print_string, 4
	.eqv read_int, 5
	.eqv read_string, 8
	.eqv print_int10, 1

op: 	.byte SIZE
str1:	.asciiz "Introduza dois numeros:\n"
str2:	.asciiz "Operador [^,<<]: "
str3:	.asciiz "Erro :-(!\n"
str4:	.asciiz "Resultado = "

	.text
	.globl main
	
main:	la $a0, str1
	li $v0, print_string
	syscall
	
	li $v0, read_int
	syscall
	move $t0, $v0
	
	li $v0, read_int
	syscall
	move $t1, $v0
	
	la $a0, str2
	li $v0, print_string
	syscall
	
	la $a0, op
	li $a1, SIZE
	li $v0, read_string
	syscall
	
	la $t6, op
	lb $t4, 0($t6)
	lb $t5, 1($t6)
	
if1: 	bne $t4, '^', if2
	
	xor $t2, $t0, $t1
	
	j print
	
if2: 	bne $t4, '<', if3
	
	bne $t4, $t5, if3
	
	sllv $t2, $t0, $t1
	
	j print
	
if3: 	li $t3, 1
	
	j erro
	
erro: 	li $v0, print_string
	la $a0, str3
	syscall
	
	j final
	
print: 	li $v0, print_string
	la $a0, str4
	syscall
	
	li $v0, print_int10
	move $a0, $t2
	syscall
	
final: 	jr $ra
