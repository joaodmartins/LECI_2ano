#extra 1 a)

# gray $t0
# mask $t1
# bin $t2
 	.data
str1: 	.asciiz "Introduza um numero: "
str2: 	.asciiz "\nO valor em binário é: "
str3: 	.asciiz "\nValor em código Gray: "
 	.eqv print_string,4
 	.eqv read_int,5
 	.eqv print_int16,34
  	.text
 	.globl main
main: 	la $a0,str1
 	li $v0,print_string 		# (instrução virtual)
 	syscall 			# print_string(str1);
 	
 	ori $v0,$0,read_int		# gray=read_int();
 	syscall 			# gray=read_int();
 	or $t0,$v0,$0 			# gray=read_int();
 	
	srl $t1,$t0,1			#mask = gray >> 1; 
	
	or $t2,$t0,$0			#bin = gray; 

for: 	beq $t1,$0,endfor 		# while(mask != 0) 

 	xor  $t2,$t2,$t1		#bin = bin ^ mask; 
 			
 	srl $t1,$t1,1			# mask = mask >> 1; 
 					
 	j for 				# }
endfor: 	
			
 	la $a0,str3			# print_string("...");
	li $v0,print_string  		# print_string("...");
 	syscall 			# print_string("...");
 	
 	or $a0,$t0,$0			# print_int16(gray); 
	ori $v0,$0,print_int16 		# print_int16(gray); 
 	syscall 			# print_int16(gray); 
 	
 	la $a0,str2			# print_string("...");
	li $v0,print_string  		# print_string("...");
 	syscall 			# print_string("...");
 	
 	or $a0,$t2,$0			# print_int16(bin); 
	ori $v0,$0,print_int16 		# print_int16(bin); 
 	syscall 			# print_int16(bin); 
 	
 	jr $ra 				# fim do programa 
