#1a

# i: $t0
# lista: $t1
# lista + i: $t2 

  	.data
  	.align 2
lista:	.space 20		##atençao ao tamanho 4*5
str:	.asciiz "\nIntroduza um numero: "
 	.text
 	.globl main
main: 	la $t1,lista		#static int lista[SIZE]; 
	
	li $t0,0		#int i =0;
	
while:	bgeu $t0,20,end_w	# i < SIZE

	la $a0,str
	li $v0,4
	syscall 
	
	li $v0,5
	syscall 
	
	addu $t2,$t1,$t0	
	sw $v0,0($t2)

	addi $t0,$t0,4		#i++
	j while
end_w: