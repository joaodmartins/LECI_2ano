# Mapa de registos
#
# res: 		$v0
# s: 		$a0
# *s: 		$t0
# digit: 	$t1

	.data
	.eqv print_int10, 1
	.eqv exit, 10
	
str: 	.asciiz "2020 e 2024 sao anos bissextos"
	.text
	.globl main
	
atoi: 	li $v0, 0
	li $t2, 48

while: 	lb $t0, 0($a0)
	blt $t0, '0', endw
	bgt $t0, '9', endw
	
	subu $t1, $t0, $t2
	addiu $a0, $a0, 1
	
	mulu $v0, $v0, 10
	addu $v0, $v0, $t1
	
	j while

endw: 	jr $ra

main: 	la $a0, str
	jal atoi
	
	move $a0, $v0
	li $v0, print_int10
	syscall
	
	li $v0, exit
    	syscall 
	
	