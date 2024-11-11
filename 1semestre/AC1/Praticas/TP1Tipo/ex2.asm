# Mapa de registos
# 
# i:		$t0
# v:		$t1

	.data
	.eqv SIZE, 8
	.eqv print_string, 4
	.eqv print_int10, 1
	.eqv print_char, 11
	
val: 	.word 8, 4, 15, -1987, 327, -9, 27, 16
str1: 	.asciiz "Result is: "

	.text 
	.globl main
	
main: 	li $t0, 0

do1: 	la $t2, val		# v = &val[0]
	sll $t3, $t0, 2		# $t3 = i * 4
	addu $t3, $t2, $t3	# v = &val[i]
	lw $t1, 0($t3)		# v = val[i]
	
	li $t4, SIZE		# $t4 = SIZE
	div $t4, $t4, 2		# $t4 = SIZE / 2
	addu $t4, $t4, $t0	# $t4 = i + SIZE / 2
	sll $t4, $t4, 2 	# $t4 = (i + SIZE / 2) * 4
	addu $t4, $t2, $t4	# $t4 = &val[i + SIZE / 2]
	lw $t5, 0($t4)		# $t5 = val[i + SIZE / 2]
	sw $t5, 0($t3) 		# val[i] = val[i + SIZE / 2]
	sw $t1, 0($t4)		# val[i + SIZE / 2] = v
	
	addi $t0, $t0, 1
	
	li $t6, SIZE
	div $t6, $t6, 2	
	
while1:	bge $t0, $t6, enddw1
	
	j do1
	
enddw1: li $v0, print_string
	la $a0, str1
	syscall
	
	li $t0, 0
	
do2: 	la $t2, val		# $t7 = &val[0]
	sll $t7, $t0, 2		# $t0 = i * 4
	addu $t7, $t2, $t7 	# $t7 = &val[i]
	lw $a0, 0($t7)		# $a0 = val[i]
	
	addi $t0, $t0, 1
	
	li $v0, print_string
	syscall

	li $v0, print_char
	li $a0, ','
	syscall
	
while2:	bge $t0, SIZE, endw2
	
	j do2
	
endw2:	jr $ra
	
	
	
	
	
	
