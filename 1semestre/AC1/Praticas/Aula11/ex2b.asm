# typedef struct
# {				Align	Size 	Offset
#    unsigned int id_number;	  4	 4	  0	
#    char first_name[18];	  1	 18	0+4=4
#    char last_name[15];	  1	 15	4+18=22
#    float grade;		  4	 4	22+15=37->40
# } student			  4	 44
	
	.data
	.eqv print_string, 4
	.eqv print_intu10, 36
	.eqv print_char, 11
	.eqv print_float, 2
	
stg: 	.word 70284
	.asciiz "João"
	.space 13
	.asciiz "Martins"
	.space 7
	.float 13.9

str1:	.asciiz "\nN. Mec: "
str2:   .asciiz "\nNome: "
str3:   .asciiz "\nNota: "

	.text
	.globl main
	
main:	la $t0, stg
	
	# N. Mec
	la $a0, str1
	li $v0, print_string
	syscall
	lw $a0, 0($t0) 
	li $v0, print_intu10
	syscall
	
	# Primeiro e Ultimo nome
	la $a0, str2
	li $v0, print_string
    	syscall
    	addiu $a0, $t0, 22 
    	li $v0, print_string
    	syscall
 
    	li $a0, ','
    	li $v0, print_char
    	syscall    	
   	addiu $a0, $t0, 4
    	li $v0, print_string
    	syscall
	
	# Nota
	la $a0, str3
	li $v0, print_string
	syscall
	
	l.s $f12, 40($t0)
    	li $v0, 2
    	syscall
	
	jr $ra