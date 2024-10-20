#define SIZE 5
#void main(void)
#{
#	static int lista[SIZE]; // declara um array de inteiros
#				// residente no segmento de dados
#	int i;
#	for(i=0; i < SIZE; i++)
#	{
#		print_string("\nIntroduza um numero: ");
#		lista[i] = read_int();
#	}
#}

	.data
	.eqv SIZE, 5				#define SIZE 5
	.eqv print_str, 4
	.eqv read_int, 5
str:	.asciiz "\nIntroduza um numero: "
	.align 2	
lista:	.space 20				#static int lista[SIZE]; // declara um array de inteiros
						#			 // residente no segmento de dados	
	.text
	.globl main
main:						#void main(void)
						#{

	li $t0, 0				#	int i=0;
for:	bge $t0, SIZE, endFor			#	while (i<SIZE)
						#	{
	la $a0, str
	li $v0, print_str			#		print_string("\nIntroduza um numero: ");
	syscall
	
	li $v0, read_int			#		int temp = read_int();
	syscall
	sll $t1, $t0, 2				#		int temp1 = i+4
	la $t2, lista
	addu $t2, $t2, $t1			#		int *temp2 = temp1 + &(lista[0]);
	sw $v0, 0($t2)				#		lista[i] = temp;
										
	addi $t0, $t0, 1			#		(i++)
	j for					#	}
endFor:

	jr $ra					#}

	
	
	
	
	