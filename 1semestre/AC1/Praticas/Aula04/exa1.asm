# Mapa de registos
# 
# p: 	$t0
# *p:	$t1

	.data
	.eqv SIZE, 20
	.eqv print_string, 4
	.eqv read_string, 8
	
str: 	.space 21				# Reserva 21 bytes para a string do usuário (20 + 1 para o terminador nulo)
str1: 	.asciiz "Introduza uma string: "	# Mensagem que solicita a entrada de uma string
	
	.text
	.globl main
	
main:	# Exibe a mensagem "Introduza uma string: "
	li $v0, print_string
	la $a0, str1
	syscall
	
	# Lê uma string do usuário e armazena em str
	li $v0, read_string
	la $a0, str
	li $a1, SIZE
	syscall
	
	# Configura o ponteiro p para o início de str
	la $t0, str
	
while: 	lb $t1, 0($t0) # Carrega o caractere em $t1
	
	beq $t1, '\0', endw # Verifica se *p == '\0'
	
	li $t2, 'a'		# Coloca o valor ASCII de 'a' em $t2
	li $t3, 'A'		# Coloca o valor ASCII de 'A' em $t3
	sub $t1, $t1, $t2	# Calcula *p - 'a'
	add $t1, $t1, $t3	# Calcula *p - 'a' + 'A'
	
	sb $t1, 0($t0)		# Armazena o caractere convertido em *p
	
	addi $t0, $t0, 1	# p++
	
	j while
	
endw:	# Exibe a string convertida
	li $v0, print_string
	la $a0, str
	syscall 
	
	jr $ra