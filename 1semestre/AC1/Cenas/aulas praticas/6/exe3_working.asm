# i = $t0
# j = $t1

	.data
	.eqv print_string,4
	.eqv print_int10,1
	.eqv print_char,11
	.eqv SIZE,3
str1:	.asciiz "Array"
str2:	.asciiz "de"
str3:	.asciiz "ponteiros"
str4:	.asciiz ": "
str5: 	.asciiz "\nString #"
array:	.word str1,str2,str3
	.text
	.globl main
	
main:	li $t0,0		# i = 0;

for:	bge $t0,SIZE,endfor	# i < SIZE

	la $a0,str5
	li $v0,print_string
	syscall			# print_string("\nString #") ;
	
	or $a0,$0,$t0		# $a0 = i ;
	li $v0,print_int10
	syscall			# print_int10( i );
	
	la $a0,str4
	li $v0,print_string
	syscall			# print_string (": ")
	
	li $t1,0		# j = 0;
	
	la $t2,array		# $t2 = &array[0][0] ;
	sll $t3,$t0,2		# $t3 = i * 4 ;
	addu $t3,$t3,$t2	# $t3 = &array[i][0] ;
	lw $t3,0($t3)		# $t3 = array[i][0] = &str1[0];
	addu $t4,$t3,$t1	# $t4 = array[i][j] = &str1[j];
	lb $t4,0($t4)		# $t4 = str1[j] ;
	
	
while:	beq $t4,'\0',endwhile	# while(array[i][j] != '\0')
	
	move $a0,$t4		# $a0 = array[i][j] ;
	li $v0,print_char
	syscall			# print_char(array[i][j])
	
	li $a0,'-'
	li $v0,print_char
	syscall			# print_char('-')
	
	addi $t1,$t1,1		# j++;
	
	addu $t4,$t3,$t1	# $t4 = array[i][j] = &str1[j];
	lb $t4,0($t4)		# $t4 = str1[j] ;
	
	j while
endwhile:
	addi $t0,$t0,1		# i++;
	j for
endfor:	
	jr $ra
	
