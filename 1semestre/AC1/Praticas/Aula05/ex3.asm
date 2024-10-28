# Mapa de registos
# 
# houve_troca:	$t4
# i: 		$t5
# lista: 	$t6
# lista + i: 	$t7

	.data
	.eqv SIZE, 10
	.eqv TRUE, 1
	.eqv FALSE, 0
	.align 2
lista: 	.word 10
str1: 	.asciiz "Introduza um numero: "
str2: 	.asciiz "\nConteudo do array ordenado:\n"
str3: 	.asciiz "; "
str4: 	.asciiz "\n"

	.text
	.globl main
	
main:	la $t6, lista
	li $t5, 0
	
for:
	bge $t6, SIZE, dowhile
	
	li $v0, 4
	la $a0, str1
	syscall
	
	li $v0, 5
	syscall
	sw $v0, 0($t6)
	
	addiu $t6, $t6, 4
	
	j for
	
dowhile: 
	li $t4, FALSE
	
	bge $t5, SIZE, enddw
	
	

	
	
	
	