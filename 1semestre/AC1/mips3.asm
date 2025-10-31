# Mapa de registos
# 
#
#
# houve_troca:	$t4
# i:		$t5
# lista:	$t6
# lista + i:	$t7

	.data
	.eqv SIZE, 10
	.eqv TRUE, 1
	.eqv FALSE 0
	
lista:	.space 40
str1:	.asciiz "\nIntroduza 10 números:\n"
str2:	.asciiz "; "
str3:	.asciiz "\nConteudo do array ordenado:\n"

	.text
	.globl main
	
main:	