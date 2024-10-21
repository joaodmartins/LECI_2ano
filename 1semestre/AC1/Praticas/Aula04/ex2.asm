# Mapa de resgistos
# num:	$t0
# p:	$t1
# *p:	$t2
	
	.data
	.eqv SIZE, 20        # Defini��o do tamanho m�ximo da string
	.eqv read_string, 8
	.eqv print_int10, 1
	
str:    .space 21           # Espa�o para 20 caracteres + terminador '\0'

	.text
    	.globl main

main:
    	# Syscall para ler a string
    	li $v0, read_string	# C�digo da syscall para leitura de string
    	la $a0, str            	# Endere�o da string
    	li $a1, SIZE		# Tamanho m�ximo (20 + 1 para '\0')
    	syscall			# Chama a syscall

    	# Inicializa contadores
    	li $t0, 0 		# num = 0 (contador de d�gitos)
    	la $t1, str		# p = str (ponteiro para o in�cio da string)

while:
    	lb $t2, 0($t1)		# Carrega byte da posi��o p (str[i]) em $t2
    	beq $t2, $zero, endw 	# Se *p == '\0', termina o loop

if:
    	# Verifica se o caractere � um d�gito ('0' <= *p <= '9')
    	li $t3, '0'		# Carrega '0' em $t3
    	blt $t2, $t3, endif	# Se *p < '0', pula para skip_count
    	li $t3, '9'		# Carrega '9' em $t3
    	bgt $t2, $t3, endif	# Se *p > '9', pula para skip_count

    addi $t0, $t0, 1		# Incrementa num se *p for um d�gito

endif:
    addi $t1, $t1, 1		# Incrementa ponteiro p (p++)
    j while			# Volta para o in�cio do loop

endw:
    # Imprime o n�mero de d�gitos
    move $a0, $t0		# Prepara o valor de num (contador de d�gitos) para impress�o
    li $v0, print_int10		# C�digo da syscall para imprimir inteiros
    syscall			# Chama a syscall

    # Finaliza o programa
    jr $ra			# Chama a syscall

	
