# Mapa de registos
#	
# n: 		$a0 -> $s0
# b: 		$a1 -> $s1
# s: 		$a2 -> $s2
# p: 		$s3
# digit:	$t0
# Sub-rotina intermedia
	
	.data
	.eqv MAX_STR_SIZE, 33
	.eqv read_int, 5
	.eqv print_string, 4
	
str: 	.space 34

	.text
	.globl main
	
toascii: 
	addiu $a0, $a0, '0'

if: 	ble $a0, '9', endif

	addi $a0, $a0, 7
	
endif: 	move $v0, $a0
	
	jr $ra
	
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
	
itoa: 	addiu $sp, $sp, -20
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	sw $s1, 8($sp)
	sw $s2, 12($sp)
	sw $s3, 16($sp)

	move $s0, $a0  	# n 
	move $s1, $a1	# b
	move $s2, $a2	# s
	move $s3, $a2	# p = s
	
do: 	rem $t0, $s0, $s1
	div $s0, $s0, $s1
	
	move $a0, $t0
	jal toascii
	
	sb $v0, 0($s3)
	addiu $s3, $s3, 1
	
while: 	blez $s3, enddw

	j do
	
enddw: 	sb $0, 0($s3)
	
	move $a0, $s2
	jal strrev
	
	move $v0, $s2
	
	lw $s3, 16($sp)
	lw $s2, 12($sp)
	lw $s1, 8($sp)
	lw $s0, 4($sp)
	lw $ra, 0($sp)
	addiu $sp, $sp, 20
	
main:	addiu $sp, $sp, -12
    	sw $ra, 8($sp)
    	sw $s0, 4($sp)
    	sw $s1, 0($sp)
    	
do1:	li $v0, read_int
    	syscall
    	move $s1, $v0           # Guarda o valor lido em $s1

    	# Converte e imprime o valor em diferentes bases
    	la $a2, str             # Carrega o endereço do buffer

   	# Base 2
    	move $a0, $s1           # Primeiro argumento (n)
    	li $a1, 2               # Segundo argumento (b)
    	jal itoa
    	li $v0, print_string    # Código de syscall para print_string
    	syscall

    	# Base 8
    	move $a0, $s1           # Primeiro argumento (n)
    	li $a1, 8               # Segundo argumento (b)
   	jal itoa
    	li $v0, print_string    # Código de syscall para print_string
    	syscall

    	# Base 16
    	move $a0, $s1           # Primeiro argumento (n)
    	li $a1, 16              # Segundo argumento (b)
    	jal itoa
    	li $v0, print_string    # Código de syscall para print_string
    	syscall

    	# Condição de saída do loop
    	bne $s1, $0, do1            # Se val != 0, repete o loop

    	# Restaurando os registradores e terminando o programa
    	lw $s1, 0($sp)
    	lw $s0, 4($sp)
    	lw $ra, 8($sp)
    	addiu $sp, $sp, 12
    	li $v0, 10              # Syscall para terminar o programa
    	syscall