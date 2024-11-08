# Mapa de registos
#
# a: $t0
# b: $t1
# i: $t2
# j: $t3

	.data
	.eqv read_string, 8
	.eqv read_int, 5
	.eqv print_string, 4

str1: 	.space 25
str2: 	.space 25

	.text
	.globl main
	
main: 	li $v0, read_string
	la $a0, str1
	li $a1, 25
	syscall
	
	li $v0, read_int
	syscall
	move $t0, $v0
	
	li $v0, read_int
	syscall
	move $t1, $v0
	
	la $t4, str2 		# $t4 = &str2[0]
	li $t5, '\0'
	sb $t5, 0($t4)
	
	li $t2, 0
	li $t3, 0
	
if: 	ble $t1, $t0, endif
	
	la $t6, str1		# $t6 = &str1[0]
	addu $t7, $t6, $t2	# $t7 = &str1[i]
	lb $t8, 0($t7)		# $t8 = str1[i]
	
while1:	bge $t2, $t0, while2
	
	beq $t8, '\0', while2
	
	addi $t2, $t2, 1
	
	j while1
	
while2: bgt $t2, $t1, endw2
		
	beq $t8, '\0', endw2
	
	addu $t4, $t4, $t3
	sb $t8, 0($t4)
	
	addi $t2, $t2, 1
	addi $t3, $t3, 1
	
	j while2

endw2:	la $t4, str2 		
	addu $t4, $t4, $t3
	li $t5, '\0'
	sb $t5, 0($t4)
	
endif: 	li $v0, print_string
	la $a0, str2
	syscall
	
	jr $ra
	
	
	
