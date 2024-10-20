#extra 2c)

# $t0 res
# $t1 i
# $t2 mdor
# $t3 mdo
 	.data
str1: 	.asciiz "Introduza dois numeros: "
str2: 	.asciiz "Resultado: "
 	.eqv print_string,4
 	.eqv read_int,5
 	.eqv print_int10,1
  	.text
 	.globl main
main: 	li $t0,0			# res=0
	li $t1,0			# i=0
	
	la $a0,str1			#
 	li $v0,print_string 		# (instrução virtual)
 	syscall 			# print_string(str1);
 	
 	ori $v0,$0,read_int		# mdor=read_int();
 	syscall 			# mdor=read_int();
 	or $t2,$v0,$0 			# mdor=read_int();
 	
 	andi $t2,$t2,0xFFFF		# mdor = read_int() & 0xFFFF; 
 	
 	ori $v0,$0,read_int		# mdo=read_int();
 	syscall 			# mdo=read_int();
 	or $t3,$v0,$0 			# mdo=read_int();
 	
 	andi $t3,$t3,0xFFFF		# mdo = read_int() & 0xFFFF; 
 	
while:	beq $t2,$0,end_w		# while( (mdor != 0) && (i++ < 16) ) 
	bge $t1,16,end_w		# while( (mdor != 0) && (i++ < 16) ) 
	
	andi $t4,$t2,0x00000001		# (mdor & 0x00000001)
	beq $t4,$0,end_if		#if( (mdor & 0x00000001) != 0 ) 
	add $t0,$t0,$t3			#res = res + mdo; 
end_if:	
	
	sll $t3,$t3,1
	srl $t2,$t2,1
	
	addi $t1,$t1,1
	j while
end_w:	
	la $a0,str2			#
 	li $v0,print_string 		# (instrução virtual)
 	syscall 			# print_string(str1);

 	or $a0,$t0,$0			# print_int10(res); 
	ori $v0,$0,print_int10 		# print_int10(res); 
 	syscall 			# print_int10(res); 


