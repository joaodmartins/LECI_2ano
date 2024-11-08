# Mapa de registos
#
# n_even:	$t0 		
# n_odd: 	$t1
# p1:		$t2
# p2:		$t3

	.data
	.eqv SIZE, 5
	.eqv read_int, 5
	.eqv print_int10, 1
	
array_a:      .space 20
array_b:      .space 20    

	.text
	.globl main
	
main: 	li $t0, 0	# n_even = 0
	li $t1, 0	# n_odd = 0
	la $t2, array_a	# p1 = a
	
	addi $t4, $t4, SIZE 	# $t4 = SIZE
	sll $t4, $t4, 2		# $t4 = SIZE * 4
	add $t4, $t4, $t2	# $t4 = a + 2
	
for1: 	bge $t2, $t4, endfor1
	
	li $v0, read_int
	syscall
	sw $v0, 0($t2)
	
	addi $t2, $t2, 4
	
	j for1
	
endfor1: la $t2, array_a
	la $t3, array_b
	
for2: 	bge $t2, $t4, endfor2
	
	lw $t5, 0($t2)
	rem $t6, $t5, 2

if: 	beq $t6, $zero, else

	addi $t3, $t3, 4
	sw $t5, 0($t3)
	
	addi $t1, $t1, 1
	
	addi $t2, $t2, 1
	
	j for2
	
else: 	addi $t0, $t0, 1

	addi $t2, $t2, 1
	
	j for2	

endfor2: la $t3, array_b
	sll $t5, $t1, 2
	add $t6, $t5, $t3
		
for3: 	bge $t3, $t6, endfor3
	
	lw $t7, 0($t3)
	li $v0, print_int10
	move $a0, $t7
	syscall
	
	j for3
	
endfor3: jr $ra
	
	
	
	
	
	
	
