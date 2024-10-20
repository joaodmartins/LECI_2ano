#define SIZE 3
#void main(void)
#{
# static char *array[SIZE]={"Array", "de", "ponteiros"};
# int i, j;
# for(i=0; i < SIZE; i++)
# {
# print_str( "\nString #" );
# print_int10( i );
# print_str( ": " );
# j = 0;
# while(array[i][j] != '\0')
# {
# print_char(array[i][j]);
# print_char('-');
# j++;
# }
# }
#} 

  	.data
str1:	.asciiz "Array"
str2:	.asciiz "de"
str3:	.asciiz "ponteiros"
lista:	.word str1, str2, str3
 	.eqv print_char,11
 	.eqv print_string,4
 	.eqv print_int10,1
 	.eqv SIZE,3 
 	.text
 	.globl main  
main: 	la $t1, lista 	# $t2 = &(array[0]);
	li $t0, 0 	# i = 0;
	
	li $t3, SIZE
	
for:	bgeu $t0,$t3,end_f

	or $a0,$t0,$0
	ori $v0,$0,print_int10
	syscall				# print_int10( i );
	
	lw $t4,0($t1)
	
	or $a0,$t4,$0
	ori $v0,$0,print_string
	syscall				# print_str( "\nString #" );

	lb $t5,0($t4)	
for2:	beq $t5,'\0',end_f2

	or $a0,$t5,$0
	ori $v0,$0,print_char
	syscall				# print_str( "\nString #" );
	
	lb $t5,0($t4)
	addi $t4,$t4,1
end_f2:	
	addi $t1,$t1,4
	addi $t0,$t0,1
		
end_f:	jr $ra		
				