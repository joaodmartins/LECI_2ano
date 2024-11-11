# Mapa de registos
#
# a: 	$t0
# b:	$t1
# i:	$t2
# j:	$t3

	.data
	.eqv SIZE, 25
	.eqv read_string, 8
	.eqv read_int, 5
	.eqv print_string, 4
	
str1: 	.space 25
str2: 	.space 25
	
	.text
	.globl main
	
main:  	li $v0, read_string
	la $a0, str1
	li $a1, SIZE
	syscall
	
	li $v0, read_int
	syscall
	move $t0, $v0
	
	li $v0, read_int
	syscall
	move $t1, $v0
	
	la $t4, str2
	li $t5, '\0'
	sb $t5, 0($t4)
	
	li $t2, 0
	li $t3, 0
	
if: 	ble $t1, $t0, endif

	la $t6, str1		# $t6 = &str1[0]
	addu $t6, $t6, $t2	# $t6 = &str1[i]
	lb $t6, 0($t6)		# $t6 = str1[i]
	
while1:	bge $t2, $t0, endw1	
	
	beq $t6, '\0', endw1
	
	addi $t2, $t2, 1
	
endw1: 	
	
while2: bgt $t2, $t1, endw2
	
	beq $t6, '\0', endw2
	
	la $t7, str2
	
	addu $t7, $t7, $t3
	
	sb $t6, 0($t7)
	
	addi $t2, $t2, 1
	
	addi $t3, $t3, 1

endw2:	la $t7, str2
	addu $t7, $t7, $t3
	li $t8, '\0'
	sb $t8, 0($t7)
	
endif: 	lb $a0, 0($t7)
	li $v0, print_string
	syscall
	
	jr $ra