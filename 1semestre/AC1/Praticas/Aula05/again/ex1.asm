# i: 		$t0
# lista:	$t1
# lista + i:	$t2
	
	.data
	.eqv SIZE, 5
	.eqv print_string, 4
	.eqv read_int, 5
	
lista:	.space 20		# SIZE * 4
str: 	.asciiz "\nIntroduza um numero: "

	.text
	.globl main
	
main:	li $t0, 0		# i = 0
	
while:	bge $t0, SIZE, endw	# while(i < SIZE) {

	la $a0, str
	li $v0, print_string
	syscall			# print_string("\nIntroduza um numero: ")
	
	li $v0, read_int
	syscall			# $v0 = read_int()
	
	la $t1, lista		# $t1 = lista (ou &lista[0])
	sll $t2, $t0, 2		# multiplica i por 4
	addu $t2, $t2, $t1	# $t2 = &lista[i]
	sw $v0, 0($t2)		# lista[i] = read_int();
	addi $t0, $t0, 1	# i++
	
	j while
	
endw:	jr $ra
	
	
	
	