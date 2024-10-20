    	.data
str1: 	.asciiz "Introduza um numero: "      # Mensagem para pedir número
str2: 	.asciiz "Valor ignorado\n"           # Mensagem de valor ignorado
str3: 	.asciiz "A soma dos positivos e': "  # Mensagem para a soma final

    	.text
    	.globl main
main:
    	li $t0, 0             	# soma = 0
    	li $t2, 0             	# i = 0

for:
    	bge $t2, 5, endfor    	# while (i < 5)

    	# print_string("Introduza um numero: ");
    	li $v0, 4             	# Syscall para imprimir string
    	la $a0, str1          	# Carregar endereço da string em $a0
    	syscall               	# Chama o syscall

    	# value = read_int();
    	li $v0, 5             	# Syscall para ler inteiro
    	syscall               	# Chama o syscall
    	move $t1, $v0         	# value = $v0 (resultado da leitura)

    	# if (value > 0)
    	blez $t1, else        	# Se value <= 0, salta para else

    	# soma += value
    	add $t0, $t0, $t1     	# soma = soma + value
    	j endif               	# Salta para o fim do if

else:
    	# print_string("Valor ignorado\n");
    	li $v0, 4             	# Syscall para imprimir string
    	la $a0, str2          	# Carregar endereço da string em $a0
    	syscall               	# Chama o syscall

endif:
    	addi $t2, $t2, 1      	# i++

    	j for                 	# Volta para o início do loop

endfor:
    	# print_string("A soma dos positivos e': ");
    	li $v0, 4             	# Syscall para imprimir string
    	la $a0, str3          	# Carregar endereço da string em $a0
    	syscall               	# Chama o syscall

    	# print_int10(soma);
    	li $v0, 1             	# Syscall para imprimir inteiro
    	move $a0, $t0         	# Passa a soma (valor em $t0) para $a0
    	syscall               	# Chama o syscall

    	# Finaliza o programa
    	li $v0, 10            	# Syscall para encerrar o programa
    	syscall
