	.data
	.eqv STR_MAX_SIZE, 30
	
str1: 	.asciiz "I serodatupmoC ed arutetiuqrA"
str2: 	.space 31
strtl: 	.asciiz "String too long: "

	.text
	.globl main
	
strcpy: # Salva o registrador $ra na pilha
    	addiu $sp, $sp, -8        # Reserva espaço na stack
    	sw $ra, 0($sp)            # Guarda o endereço de retorno
    	sw $s0, 4($sp)            # Salva $s0
    
    	# Inicializa os registradores para src e dst
    	move $s0, $a0             # dst -> $s0
    	move $t0, $a0             # dst em $t0, que será retornado no final
    	move $t1, $a1             # src -> $t1
	
dow: 	lb $t2, 0($t1)            # Carrega src[i] em $t2
    	sb $t2, 0($s0)            # Copia src[i] para dst[i]
    	addi $s0, $s0, 1          # dst++
    	addi $t1, $t1, 1          # src++
    	bne $t2, '\0', dow         # Continua até encontrar o caractere nulo ('\0')

	# Restaura $ra e $s0 e retorna
    	move $v0, $t0             # Retorna o ponteiro dst (valor original de dst em $t0)
    	lw $ra, 0($sp)            # Restaura $ra
    	lw $s0, 4($sp)            # Restaura $s0
    	addiu $sp, $sp, 8         # Libera espaço da stack
    	jr $ra                    # Retorna
    	
strlen: li $t1, 0              # Inicializa o contador de comprimento em 0
    	move $t2, $a0          # Salva o endereço inicial da string em $t2

while:  lb $t0, 0($t2)         # Carrega o próximo caractere
    	beq $t0, '\0', endw    # Se for o caractere nulo, termina o loop
    	addi $t2, $t2, 1       # Incrementa o endereço (usando $t2 agora)
    	addi $t1, $t1, 1       # Incrementa o contador

    	j while

endw:   move $v0, $t1          # Move o comprimento da string para $v0
    	jr $ra                 # Retorna para main
    	
exchange: # Salva $t0 para uso temporário
    	lb $t0, 0($a0)          # Carrega o valor de *c1 em $t0
    	lb $t1, 0($a1)          # Carrega o valor de *c2 em $t1
    	sb $t1, 0($a0)          # *c1 = *c2
    	sb $t0, 0($a1)          # *c2 = aux (original *c1)
    	jr $ra                  # Retorna

strrev:	# Salva registradores e prepara a pilha
    	addiu $sp, $sp, -16      # Reserva espaço na stack
    	sw $ra, 0($sp)           # Guarda endereço de retorno
    	sw $s0, 4($sp)           # Guarda valor de $s0
    	sw $s1, 8($sp)           # Guarda valor de $s1
    	sw $s2, 12($sp)          # Guarda valor de $s2
    
    	# Inicializa os ponteiros p1 e p2
    	move $s0, $a0            # str -> $s0 (argumento)
    	move $s1, $a0            # p1 = str
    	move $s2, $a0            # p2 = str

while1:                      	  # while (*p2 != '\0') {
	lb $t0, 0($s2)           # Carrega o valor de *p2 em $t0
    	beq $t0, '\0', endwhile1 # Se *p2 == '\0', sai do loop
    	addi $s2, $s2, 1         # p2++
    	j while1                 # Repete o loop
endwhile1:
    	addi $s2, $s2, -1        # p2--

while2:                          # while (p1 < p2) {
    	slt $t1, $s1, $s2        # Verifica se p1 < p2
    	beq $t1, 0, endwhile2    # Se não, termina o loop

    	# Chamada para exchange(p1, p2)
    	move $a0, $s1            # Primeiro argumento: p1
    	move $a1, $s2            # Segundo argumento: p2
    	jal exchange             # Chama exchange(p1, p2)

    	# Incrementa p1 e decrementa p2
    	addi $s1, $s1, 1         # p1++
    	addi $s2, $s2, -1        # p2--
    	j while2                 # Repete o loop
    	
endwhile2:

    	# Retorna o ponteiro inicial (str)
    	move $v0, $s0            # Coloca o valor de str em $v0 (valor de retorno)

    	# Restaura os valores dos registradores salvos e termina a sub-rotina
    	lw $ra, 0($sp)           # Restaura endereço de retorno
    	lw $s0, 4($sp)           # Restaura $s0
    	lw $s1, 8($sp)           # Restaura $s1
    	lw $s2, 12($sp)          # Restaura $s2
    	addiu $sp, $sp, 16       # Libera espaço da stack
    	jr $ra                   # Retorna
	
main:
    # Verifica o tamanho de str1 com strlen
    la $a0, str1            # Carrega o endereço de str1 em $a0
    jal strlen              # Chama strlen(str1)
    move $t0, $v0           # Salva o comprimento de str1 em $t0

    # Compara o comprimento de str1 com STR_MAX_SIZE
    li $t1, 30              # Carrega STR_MAX_SIZE em $t1
    ble $t0, $t1, strcpy  # Se strlen(str1) <= STR_MAX_SIZE, continua

    # Caso a string seja muito longa
    la $a0, strtl    # Carrega o endereço da mensagem de erro em $a0
    li $v0, 4               # Syscall para imprimir string
    syscall
    
    # Imprime o comprimento da string (strlen(str1))
    move $a0, $t0           # Coloca strlen(str1) em $a0
    li $v0, 1               # Syscall para imprimir inteiro
    syscall

    # Define exit_value = -1 (indicando erro)
    li $v0, -1              # Valor de retorno -1 para erro
    jr $ra             # Pula para o fim do main

	
