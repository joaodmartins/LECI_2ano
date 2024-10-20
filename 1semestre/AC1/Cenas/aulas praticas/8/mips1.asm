# Mapa de registos
# res: $v0
# s: $a0
# *s: $t0
# digit: $t1
# Sub-rotina terminal: não devem ser usados registos $sx

atoi: 	li $v0,0 		# res = 0;
while: 	lb $t0,0($a0) 		# while(*s >= ...)
 	blt $t0,'0',end_w 	#
 	bgt $t0,'9',end_w  	# {
 	sub $t1,$t0,'0' 	# digit = *s – '0'
 	addiu $a0,$a0,1 	# s++;
 	mul $v0,$v0,10 		# res = 10 * res;
 	add $v0,$v0,$t1 	# res = 10 * res + digit;
 	j while
end_w:		 		# }
 	jr $ra 			# termina sub-rotina 


#int main(void)
#{
# static char str[]="2016 e 2020 sao anos bissextos";
# print_int10( atoi(str) );
# return 0;
#} 
	.data
str:	.asciiz "2016 e 2020 sao anos bissextos"
	.eqv print_int10,1	
	.text
	.globl main
main: 	la $a0,str

	addiu $sp,$sp,-4 
	sw $ra,0($sp)		#salvaguardar o $ra
	
	jal atoi
	move $a0,$v0
	li $v0,print_int10
	syscall
	
	lw $ra,0($sp)
   	addiu $sp,$sp,4		#load $ra
   	
	jr $ra
	



