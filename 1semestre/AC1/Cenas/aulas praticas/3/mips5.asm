#2e

# Mapa de registos:
# $t0 – value
# $t1 – bit
# $t2 - i
 	.data
str1: 	.asciiz "Introduza um numero: "
str2: 	.asciiz "\nO valor em binário é: "
 	.eqv print_string,4
 	.eqv read_int,5
 	.eqv print_char,11
  	.text
 	.globl main
main: 	la $a0,str1
 	li $v0,print_string 		# (instrução virtual)
 	syscall 			# print_string(str1);
 	
 	ori $v0,$0,read_int		# value=read_int();
 	syscall 			# value=read_int();
 	or $t0,$v0,$0 			# value=read_int();
 	
 	la $a0,str2			# print_string("...");
	li $v0,print_string  		# print_string("...");
 	syscall 			# print_string("...");
 	
 	li $t2,0 			# i = 0
 	li $t6,0			# flag=0
for: 	bgeu $t2,32,endfor 		# while(i < 32) {

 	srl  $t1,$t0,31			#bit = value >> 31;
 	
 	beq $t6,1,then			##if(flag == 1 || bit != 0) 
 	bne $t1,$0,then			##if(flag == 1 || bit != 0) 
 	j end_or_if			##if(flag == 1 || bit != 0) 
 	
then: 	li $t6,1			##if(flag == 1 || bit != 0) # flag=1
 	 
 	rem $t4,$t2,4			#(i % 4)
	bne $t4,$0,end_if
	li $a0,' '			# print_char(' ');	
	li $v0,print_char 		# print_char(' ');
 	syscall 			# print_char(' ');
	
end_if:
 	addi $t6,$t1,0x30		#0x30 + bit
	
 	or $a0,$0,$t6			#print_char(0x30 + bit); 
	li $v0,print_char		#print_char(0x30 + bit); 
 	syscall 			#print_char(0x30 + bit); 
 						
end_or_if:				##if(flag == 1 || bit != 0) 
	 		
 	sll $t0,$t0,1			# value = value << 1;
 					
 	addi $t2,$t2,1			# i++;
 	j for 				# }
endfor: 				#
 	jr $ra 				# fim do programa 
