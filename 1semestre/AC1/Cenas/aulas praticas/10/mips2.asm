	.data
	
	.align 2
stg:	.space 4
	.space 18
	.asciiz "Bonaparte"
	.space 5
	.float 5.1
	
	.eqv print_str, 4
	.eqv print_int10, 1
	.eqv print_char, 11
	.eqv print_float, 2
	.eqv read_int,5
	.eqv read_string, 8
	
	.align 2
str1:	.asciiz "\nN. Mec: "
str2:	.asciiz "\nNome: "
str3:	.asciiz "\nNota: "
str4:	.asciiz "Primeiro Nome: "
						
	.text
	.globl main
	
main:	
	la $t0,stg		# $t0 é o ponteiro de stg
	
	li $v0,print_str
	la $a0,str1
	syscall 		# print_str("\nN. Mec: ");
	
	li $v0,read_int
	syscall
	sw $v0,0($t0)		# stg.id_number = read_int(); 
	
	li $v0,print_str
	la $a0,str4
	syscall 		# print_str("Primeiro Nome: "); 
	
	addiu $t2,$t0,4
	li $v0,read_string
	move $a0,$t2
	li $a1,18
	syscall
	lw $v0,0($t0)		# stg.id_number = read_int(); 	
	
	li $v0,print_str
	la $a0,str1
	syscall 		# print_str("\nN. Mec: ");
	
	lw $a0,0($t0)		# $a0=stg.id_number
	
	li $v0,print_int10
	syscall 		# print_intu10(stg.id_number); 
	
	li $v0,print_str
	la $a0,str2
	syscall 		# print_str("\nNome: "); 
	
	addiu $a0,$t0,22	# $a0=stg.last_name	
	
	li $v0,print_str
	syscall 		# print_str(stg.last_name); 
	
	li $v0,print_char
	li $a0,','
	syscall 		# print_char(',');
	
	addiu $a0,$t0,4		# $a0=stg.last_name	
	
	li $v0,print_str
	syscall 		# print_str(stg.first_name); 
	
	li $v0,print_str
	la $a0,str3
	syscall 		# print_str("\nNota: "); 
	    	
    	l.s $f12,40($t0)
	
	li $v0,print_float
	syscall 		# print_str(stg.grade); 
	
	jr $ra
	
	
	
	