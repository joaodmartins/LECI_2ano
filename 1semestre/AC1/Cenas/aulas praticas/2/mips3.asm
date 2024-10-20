	.data
	.text
	.globl main
main: 	li $t0,0x12345678 	# instrução virtual (decomposta
				# em duas instruções nativas)
				#0x12345678 1
				#0x12345678 4
				#0x12345678 16
				#0x862A5C1B 2
				#0x862A5C1B 4 
	sll $t2,$t0,1 		#deslocamento à esquerda lógico,
	srl $t3,$t0,1 		# deslocamento à direita lógico
	sra $t4,$t0,1 		# deslocamento à direita aritmético
	jr $ra 			# fim do programa
