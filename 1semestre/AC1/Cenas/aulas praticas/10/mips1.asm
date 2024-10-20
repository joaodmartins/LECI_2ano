	.data
	
	.align 2
stg:	.word 72343
	.asciiz "Napoleao"		# napoleao\0 -> 9 chars -18 = 9 de space
	.space 9
	.asciiz "Bonaparte"
	.space 5
	.float 5.1
	
	.eqv print_str, 4
	.eqv print_int10, 1
	.eqv print_char, 11
	.eqv print_float, 2
	
	.align 2
str1:	.asciiz "\nN. Mec: "
str2:	.asciiz "\nNome: "
str3:	.asciiz "\nNota: "
						
	.text
	.globl main
	
main:	li $v0,print_str
	la $a0,str1
	syscall 		# print_str("\nN. Mec: ");
	
	la $t0,stg		# $t0 é o ponteiro de stg
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
	
	
	
	