# Mapa de registos:
# str: $a0 -> $s0 (argumento é passado em $a0)
# p1:  $S1 (registo callee-saved)
# p2:  $s2 (registo callee-saved)

	.data
str: 	.asciiz "ITED - orievA ed edadisrevinU"

	.text
	.globl main
	
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
    	# Carrega o endereço da string em $a0
    	la $a0, str             # Carrega o endereço da string em $a0
    
    	# Chama a função strrev
    	jal strrev              # strrev(str)
    
    	# Chama a função print_string para imprimir a string invertida
    	move $a0, $v0           # Coloca o ponteiro da string invertida em $a0
    	li $v0, 4               # Syscall para imprimir string
    	syscall

    	# Finaliza o programa
    	li $v0, 10              # Syscall para terminar o programa
    	syscall
