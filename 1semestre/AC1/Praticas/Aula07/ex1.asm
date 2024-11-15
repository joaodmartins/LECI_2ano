	.data
	.eqv print_int10, 1

str:    .asciiz "Arquiterura de Computadores I"

	.text
	.globl main

strlen: li $t1, 0              # Inicializa o contador de comprimento em 0
    	move $t2, $a0          # Salva o endereço inicial da string em $t2

while:  lb $t0, 0($t2)         # Carrega o próximo caractere
    	beq $t0, '\0', endw    # Se for o caractere nulo, termina o loop
    	addi $t2, $t2, 1       # Incrementa o endereço (usando $t2 agora)
    	addi $t1, $t1, 1       # Incrementa o contador

    	j while

endw:   move $v0, $t1          # Move o comprimento da string para $v0
    	jr $ra                 # Retorna para main

main:   
    	la $a0, str            # Carrega o endereço da string em $a0
    	jal strlen             # Chama a função strlen

    	move $a0, $v0          # Move o resultado (comprimento da string) para $a0
    	li $v0, print_int10    # Syscall para imprimir inteiro
    	syscall

    	# Termina a execução
    	li $v0, 10             # Syscall para terminar o programa
    	syscall

	jr $ra
