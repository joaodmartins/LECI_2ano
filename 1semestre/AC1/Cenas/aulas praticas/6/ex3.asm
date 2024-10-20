	.data
str1:	.asciiz "Array"
str2:	.asciiz "de"
str3:	.asciiz "ponteiros"
array:	.word str1,str2,str3
	.eqv print_string,4
	.eqv print_int10,1
	.eqv print_char,11
	.eqv SIZE,3
strO1:	.asciiz "\nString #"
strO2:	.asciiz ": "
	.text 
	.globl main
main:	li $t0,0			#i=0
for:	bge $t0,SIZE,end_f		#for(i=0; i < SIZE; i++) {
	la $a0,strO1
	li $v0,print_string
	syscall				#print_str( "\nString #" ); 
	or $a0,$t0,$0
	li $v0,print_int10
	syscall				#print_int10( i ); 
	la $a0,strO2
	li $v0,print_string
	syscall				#print_str( ": " ); 
	li $t1,0			#j=0


while:	la $t2,array			# &array
	mul $t3,$t0,4			# i*4
	addu $t2,$t2,$t3		# &array[i][0]
	lw $t3,0($t2)			# $t3 - ponteiro a apontar para str1 2 ou 3
	
	addu $t4,$t1,$t3		# &array[i][j]
	lb $t5,0($t4)			# $t5 = array[i][j]
	
	beq $t5,'\0',end_w		#while(array[i][j] != '\0') {
	
	or $a0,$t5,$0
	li $v0,print_char
	syscall				#print_char(array[i][j]); 
	
	li $a0,'-'
	li $v0,print_char
	syscall				#print_char('-'); 
	
	addi $t1,$t1,1			#j++; 
	j while
end_w:					#}
	addi $t0,$t0,1			# i++
	j for				#}
end_f:
	jr $ra