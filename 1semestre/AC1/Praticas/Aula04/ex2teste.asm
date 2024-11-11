# Mapa de registos
#
# num: 	$t0 	
# p:	$t1
# *p:	$t2

	.data
	.eqv SIZE, 20
	.eqv read_string, 8
	.eqv print_int10, 1
	
str: 	.space 21
	
	.text
	.globl main
	
main: 	li $t0, 0		# num = 0
	
	li $v0, read_string
	la $a0, str
	li $a1, SIZE
	syscall			# read_string(str, SIZE)
	
	la $t1, str		# p = &str[0]
	
while: 	lb $t2, 0($t1)
	
	beq $t2, '\0', endw
	
if: 	blt $t2, '0', endif

	bgt $t2, '9', endif
	
	addi $t0, $t0, 1
	
endif: 	addi $t1, $t1, 1

	j while
	
endw: 	li $v0, print_int10
	move $a0, $t0
	syscall
	
	jr $ra 
	
	
