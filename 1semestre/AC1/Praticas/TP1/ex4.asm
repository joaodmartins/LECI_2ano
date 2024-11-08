# Mapa de registos
#
# p:		$t0
# i:		$t1
# maximo:	$t2
# minimo:	$t3

	.data
	.eqv MAX, 0x80000000
	.eqv MIN, 0x7FFFFFFF
	.eqv SIZE, 10
	.eqv print_string, 4
	.eqv print_int10, 1
	
val: 	.word 8, 4, -3, 5, 124, 15, -8987, 9, 27, 16
str1:	.asciiz "Maximo: "
str2:	.asciiz "\nMinimo: "

	.text
	.globl main
	
main:	la $t0, val
	li $t2, MAX
	li $t3, MIN
	li $t1, 0
	
for: 	bge $t1, SIZE, endfor
	lw $t4, 0($t0)
	ble $t4, $t2, chk_min
	move $t2, $t4
	
chk_min: bge $t4, $t3, fornext
	move $t3, $t4
	
fornext: addiu $t0, $t0, 4
	addi $t1, $t1, 1
	
	j for
	
endfor: li $v0, print_string
	la $a0, str1
	syscall
	
	li $v0, print_int10
	move $a0, $t2
	syscall
	
	li $v0, print_string
	la $a0, str2
	syscall
	
	li $v0, print_int10
	move $a0, $t3
	syscall
	
	jr $ra
	
	
	
	
