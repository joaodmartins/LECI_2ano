# define SIZE 10
# define TRUE 1
# define FALSE 0

#	void main(void)
#	{
# 		static int lista[SIZE];
# 		int houveTroca, i, aux;
# 						// inserir aqui o código para leitura de valores e
# 						// preenchimento do array
# 		for(i=0; i < SIZE-1; i++)
# 		{
# 		print_string("\nIntroduza um numero: ")
#		lista[i] = read_int
# 		}

# 		do
# 		{
# 			houveTroca = FALSE;
# 			for (i=0; i < SIZE-1; i++)
# 			{
# 				if (lista[i] > lista[i+1])
# 				{
# 					aux = lista[i];
# 					lista[i] = lista[i+1];
# 					lista[i+1] = aux;
# 					houveTroca = TRUE;
# 				}
# 			}
# 		} while (houveTroca==TRUE);
# 		// inserir aqui o código de impressão do conteúdo do array
# 		for(i=0; i < SIZE-1; i++)
# 		{
# 		print_int(lista[i])
#		print_string (";")
# 		}
#	} 



# Mapa de registos
# AUX: $t0
# *p: $t1
# lista+Size: $t2
#SIZE - 1: $t3
# houve_troca: $t4
# i: $t5
# lista: $t6
# lista + i: $t7
#
 	.data
 	.eqv FALSE,0
 	.eqv TRUE,1
 	.eqv SIZE,10
lista:	.space 40 # SIZE * 4
str1: 	.asciiz "\nIntroduza um numero: "
 	.align 2
str2: 	.asciiz "\nConteudo do array:\n"
str3: 	.asciiz "; "
 	.text
 	.eqv read_int,5
 	.eqv print_int10,1
 	.eqv print_string,4
 	.globl main

main: 	li $t0,0 #
	li $t2,SIZE #
	sub $t3,$t2,1
	li $t5,0 # i = 0;			
 	la $t6,lista 		

# código para leitura de valores
encher_lista: 	bge $t5,SIZE,after_encher # while(i < SIZE) {
 		la $a0,str1 			#print_string("introduz num ...");
		li $v0,print_string 	#print_string("introduz num ...");
		syscall                  	#print_string("introduz num ...");
 	
 		li $v0,read_int
 		syscall # $v0 = read_int();
 	
 		sll $t7,$t5,2 #
 		addu $t7,$t7,$t6 # $t7 = &lista[i]
 		sw $v0,0($t7) # lista[i] = read_int();
 	
 		addi $t5,$t5,1 # i++
 		j encher_lista # }
 		#
after_encher:	
 		li $t7,0 # lista + i = 0;
 		
 		
 #codigo para o do while		
do: 				# do {
 	li $t4,FALSE 		# houve_troca = FALSE;
 	li $t5,0 		# i = 0;
for: 	bgeu $t5,$t3,endfor		# while(i < SIZE-1){
if: 	sll $t7,$t5,2 		# $t7 = i * 4
 	addu $t7,$t7,$t6 	# $t7 = &lista[i]
 	lw $t8,0($t7) 		# $t8 = lista[i]
 	lw $t9,4($t7) 		# $t9 = lista[i+1]
 	bleu $t8,$t9,endif 	# if(lista[i] > lista[i+1]){
 	sw     $t8,4($t7)      #       lista[i+1] = $t8       
 	sw     $t9,0($t7)      #       lista[i] = $t9 
 	li $t4,TRUE 		#
 				# }
endif: 	addi $t5,$t5,1 		# i++
 	j for# }
 				
# codigo de impressao do conteudo do array
endfor:	
	beq  $t4,TRUE,do # } while(houve_troca == TRUE);
 	sll $t2,$t2,2 #
 	addu $t2,$t2,$t6 # $t2 = lista + SIZE;
imprimir: 	bgeu $t6,$t2,endProg# while(p < lista+SIZE) {
 	lw $t1,0($t6) # $t1 = *p;
 	
 	or $a0,$0,$t1 	# $a0 = t1
	li $v0,print_int10	#
	syscall  # print_int10( *p );
 	
 	la $a0,str3 			
	li $v0,print_string # print_string(...);
	syscall
 	
 	addiu $t6,$t6,4 # p++;
 	j imprimir # }
 	
endProg:	jr $ra 			# termina o programa 
