#		| Alig 	| Dim	| Offset
# id_number	| 4	| 4	| 0
# first_number 	| 1	| 18	| 0+4=4
# last_number	| 1 	| 15	| 4+18=22
# grade		| 4	| 4	| 22+15=37->40
#		| 4	| 44	| 
	
	.data
	.eqv print_string, 4
	.eqv print_float, 2
	.eqv MAX_STUDENTS,4
	
st_array:	.space 176	# Reservar 4* 44 para o array de estruturas
media:          .space 4	

	.text
	.globl main
	
main: 	addiu $sp, $sp, -4
	sw $ra, 0($sp)
	
	la $a0, st_array
	li $a1, MAX_STUDENTS
	jal read_data
	
	la $a0, st_array
	li $a1, MAX_STUDENTS
	la $a2, media
	jal max
	
	lw $ra, 0($sp)
	addiu $sp, $sp, 4
	
	jr $ra
	
	.data
	
max:	

	
	
	.data
str1:	.asciiz "N. Mec: "
str2:	.asciiz "Primeiro Nome: "
str3: 	.asciiz "Ultimo Nome: "
str4: 	.asciiz "Nota: "

	.text
	
read_data:
	move $t0, $a0
	move $t1, $a1
	li $t2, 0
	
for: 	bge $t2, $t2, endfor
	
	# Endereco do primeiro campo do estudante
	mul $t3, $t2, 44
	addu $t3, $t0, $t3
	
	# Obter numeros mecanograficos
	la $a0, str1
	li $v0, print_string
	syscall
	
	li $v0, read_string
	syscall
	sw $v0, 0($t3)
	
	# Obter primeiro nome
	la $a0, str2
	li $v0, print_string
	syscall
	
	li $v0, read_int
	addiu $a0, $t3, 4
	li $a1, 17
	syscall
	
	# Obter segundo nome
	la $a0, str3
	li $v0, print_string
	syscall
	
	li $v0, read_int
	addiu $a0, $t3, 22
	li $a1, 14
	syscall

	# Obter nota
	la $a0, str4
	li $v0, print_string
	syscall
	
	li $v0, read_float
	syscall
	s.s $f0, 40($t3) 
	
	addi $t2, $t2, 1
	
	j for

endfor:	jr $ra	

	
