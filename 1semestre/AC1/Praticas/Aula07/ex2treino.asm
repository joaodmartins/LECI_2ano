	.data
	.eqv print_string, 4
	
str1:	.asciiz "ITED - orievA ed edadisrevinU" 	

	.text
	.globl main
	
main: 	addiu $sp, $sp, -4
	sw $ra, 0($sp)
	la $a0, str1
	jal strrev
	move $a0, $v0
	li $v0, print_string
	syscall
	lw $ra, 0($sp)	
	addiu $sp, $sp, 4
	jr $ra 
	
# Mapa de registos: 	
# str: 	$a0 -> $s0
# p1:  	$s1
# p2:	$s2
	.data
	.text
		
strrev:	addiu $sp, $sp, -16
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	sw $s1, 8($sp)
	sw $s2, 12($sp)
	move $s0, $a0
	move $s1, $a0
	move $s2, $a0
	
while1:	lb $t0, 0($s2)
	beq $t0, '\0', endw1
	addiu $s2, $s2, 1
	j while1
	
endw1:	addiu $s2, $s2, -1

while2:	bge $s1, $s2, endw2
	move $a0, $s1
	move $a1, $s2
	jal exchange
	addiu $s1, $s1, 1
	addiu $s2, $s2, -1
	
	j while2

endw2:	move $v0, $s0

	lw $ra, 0($sp)
	lw $s0, 4($sp)
	lw $s1, 8($sp)
	lw $s2, 12($sp)
	addiu $sp, $sp, 16
	jr $ra
	
exchange:
	lb $t0, 0($a0)
	lb $t1, 0($a1)
	sw $t0, 0($a1)
	sw $t1, 0($a0)
	jr $ra