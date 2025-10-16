# Mapa de registos
# num:		$t0
# i:		$t1
# str:		$t2
# str+i:	$t3
# str[i]:	$t4

	.data
	.eqv	SIZE, 20
	.eqv	read_string, 8
	.eqv	print_int10, 1
str: 	.space	21
	.text
	.globl main
	
main:	la $a0, str		# int main(void) {
	li $a1, SIZE
	li $v0, read_string
	syscall			# read_str(str, SIZE)
	
	li $t0, 0		# num = 0
	li $t1, 0		# i = 0
	
while:	la $t2, str		# char *p1 = &(str[0])
	addu $t3, $t2, $t1	# char *p2 = &(str[i])
	lb $t4, 0($t3)		# char val = str[i]
	beq $t4, '\0', endw	# if (val == '\0') break

if:	blt $t4, '0', endif	# if (val >= '0' && val <= '9')
	bgt $t4, '9', endif
	addi $t0, $t0, 1	# num++
	
endif:	addi $t1, $t1, 1 	# i++
	
	j while
	
endw: 	move $a0, $t0
	li $v0, print_int10
	syscall			# print_int10(num)
	
	jr $ra
