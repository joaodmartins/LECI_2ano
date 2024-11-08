# Mapa de registos
# 
# nbr:		$t0
# c:		$t1
# p:		$t2
# pstop: 	$t3

	.data
	.eqv SIZE, 20
	.eqv SIZE4, 80
	
primos: .space SIZE4

	.text 
	.globl main

main: 	la $t2, primos
	addiu $t3, $t2, SIZE4
	
	li $t1, 2
	sw $t1, 0($t2)
	addi $t2, $t2, 1
	li $t0, 3
	
wh1: 	bge $t2, $t3, endw1
	li $t1, 2
	
wh2: 	rem $t4, $t0, $t1
	beq $t4, $zero, endw2
	
	addi $t1, $t1, 1
	
	j wh2
endw2: 	

if:	bne $t1, $t0, endif
	
	sw $t0, 0($t2)
	addi $t2, $t2, 1
	
endif: 	addi $t0, $t0, 1

	j wh1
	
endw1: 	jr $ra