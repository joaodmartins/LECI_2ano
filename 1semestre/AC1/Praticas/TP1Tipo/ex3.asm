# Mapa de registos
#
# n_even:	$t0
# n_odd:	$t1
# p1:		$t2
# p2:		$t3

	.data
	.eqv SIZE, 35
	.eqv read_int, 5
	.eqv print_int10, 1

aa:	.space 140
bb:	.space 140

	.text
	.globl main

main:	li $t0, 0
	li $t1, 0
	
	la $t2, aa			# p1 = &aa[0]
	li $t4, SIZE			# $t4 = SIZE
	sll $t4, $t4, 2			# $t4 = SIZE * 4
	addu $t5, $t4, $t2		# $t5 = aa + SIZE
	
for1: 	bgeu $t2, $t5, endfor1

	li $v0, read_int
	syscall
	sw $v0, 0($t2)			
	
endfor1: addi $t2, $t2, 1

	j for1
	
	la $t2, aa
	la $t3, bb
	
for2:	la $t3, bb
	lw $t6, 0($t2)
	
if:	remu $t7, $t6, 2
	
	beq $t7, $zero, endif
	
	sw $t6, 0($t3)
	
	addiu $t3, $t3, 4
	
	addi $t1, $t1, 1
	
	j endif
	
else: 	addi $t0, $t0, 1

endif: 	addiu $t2, $t2, 4

	j for2
	
for3: 	addu $t8, $t3, $t2
	
	bge $t2, $t8, endfor3
	
	lw $a0, 0($t3)
	
	li $v0, print_int10
	syscall
	
	addi $t3, $t3, 4
	
	j for3
	
endfor3:	jr $ra
		
 	


	
	
	
	
	
