#2a)

# Mapa de registos
# p: $t0
# *p: $t1
# lista+Size: $t2
 	.data
str1: 	.asciiz "; "
str2:	.asciiz "\nConteudo do array:\n"
lista:	.word 8,-4,3, 5, 124, -15, 87, 9, 27, 15 	# a diretiva ".word" alinha num endereço
		 					# múltiplo de 4
 	.eqv print_int10,1
 	.eqv print_string,4
 	.eqv SIZE,40
 	
 	.text
 	.globl main
main: 	la $a0,str2 			# print_string(...)
	li $v0,print_string		# print_string(...)
	syscall				# print_string(...)

 	la $t0,lista 			# p = lista
 	li $t2,SIZE 			#

 	addu $t2,$t0,$t2		# $t2 = lista + SIZE;
while: 	bgeu $t0,$t2,end_w		# while(p < lista+SIZE) {
	
 	lw $t1,0($t0) 			# $t1 = *p;
 	
 	li $v0,print_int10		# print_int10( *p );
 	or $a0,$t1,$0			# print_int10( *p );
 	syscall 			# print_int10( *p );
 	
 	la $a0,str1 			# print_string(...)
	li $v0,print_string		# print_string(...)
	syscall				# print_string(...)
	
 	addiu $t0,$t0,4 		# p++;
 	j while
end_w:					# }
 	jr $ra 				# termina o programa 
