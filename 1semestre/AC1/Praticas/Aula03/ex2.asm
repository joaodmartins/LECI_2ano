    	.data
str1:  	.asciiz "Introduza um numero: "
str2:  	.asciiz "\nO valor em bin�rio e': "

    	.eqv print_string, 4
    	.eqv read_int, 5
    	.eqv print_char, 11

    	.text
    	.globl main
main:
    	# Imprime "Introduza um numero: "
    	li $v0, print_string
    	la $a0, str1
    	syscall
    
    	# L� o n�mero do utilizador (value = read_int())
    	li $v0, read_int
    	syscall
    	move $t0, $v0
    
    	# Imprime "\nO valor em bin�rio e': "
    	li $v0, print_string 
    	la $a0, str2
    	syscall
    
    	# Inicializa o loop: i = 0
    	li $t2, 0

for:
    	# Loop para 32 bits
    	bge $t2, 32, endfor
    
    	# Imprime um espa�o a cada 4 bits
    	# Se (i % 4) == 0, imprime um espa�o
    	rem $t4, $t2, 4         # Calcula i % 4
    	bne $t4, $zero, nospace # Se n�o for m�ltiplo de 4, n�o imprime espa�o
    	li $v0, print_char
    	li $a0, ' '             # Imprime espa�o
    	syscall

nospace:
    	# Isola o bit mais significativo (31)
    	li $t3, 0x80000000
    	and $t1, $t0, $t3
    
if: 
    	# Se bit == 0, vai para 'else', sen�o imprime '1'
    	beq $t1, $zero, else
    
    	# Imprime '1'
    	li $v0, print_char         
    	li $a0, '1'             
    	syscall                 
    	j endif     
    
else:
    	# Imprime '0'
    	li $v0, print_char
    	li $a0, '0'
    	syscall

endif:
    	# Shift � esquerda para verificar o pr�ximo bit
    	sll $t0, $t0, 1
    
    	# Incrementa o contador i
    	addi $t2, $t2, 1
    
    	# Repete o loop
    	j for
    
endfor:
    	# Retorna da fun��o
    	jr $ra
	