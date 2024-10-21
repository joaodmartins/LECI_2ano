# Mapa de resgistos
# num:	$t0
# p:	$t1
# *p:	$t2
	
	.data
	.eqv SIZE, 20        # Definição do tamanho máximo da string
	.eqv read_string, 8
	.eqv print_int10, 1
	
str:    .space 21           # Espaço para 20 caracteres + terminador '\0'

	.text
    	.globl main

main:
    	# Syscall para ler a string
    	li $v0, read_string	# Código da syscall para leitura de string
    	la $a0, str            	# Endereço da string
    	li $a1, SIZE		# Tamanho máximo (20 + 1 para '\0')
    	syscall			# Chama a syscall

    	# Inicializa contadores
    	li $t0, 0 		# num = 0 (contador de dígitos)
    	la $t1, str		# p = str (ponteiro para o início da string)

while:
    	lb $t2, 0($t1)		# Carrega byte da posição p (str[i]) em $t2
    	beq $t2, $zero, endw 	# Se *p == '\0', termina o loop

if:
    	# Verifica se o caractere é um dígito ('0' <= *p <= '9')
    	li $t3, '0'		# Carrega '0' em $t3
    	blt $t2, $t3, endif	# Se *p < '0', pula para skip_count
    	li $t3, '9'		# Carrega '9' em $t3
    	bgt $t2, $t3, endif	# Se *p > '9', pula para skip_count

    addi $t0, $t0, 1		# Incrementa num se *p for um dígito

endif:
    addi $t1, $t1, 1		# Incrementa ponteiro p (p++)
    j while			# Volta para o início do loop

endw:
    # Imprime o número de dígitos
    move $a0, $t0		# Prepara o valor de num (contador de dígitos) para impressão
    li $v0, print_int10		# Código da syscall para imprimir inteiros
    syscall			# Chama a syscall

    # Finaliza o programa
    jr $ra			# Chama a syscall

	
