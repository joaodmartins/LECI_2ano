	.data
	.text
	.globl main
main: 	li $t0,0x12345678 	# instru��o virtual (decomposta
				# em duas instru��es nativas)
				#0x12345678 1
				#0x12345678 4
				#0x12345678 16
				#0x862A5C1B 2
				#0x862A5C1B 4 
	sll $t2,$t0,1 		#deslocamento � esquerda l�gico,
	srl $t3,$t0,1 		# deslocamento � direita l�gico
	sra $t4,$t0,1 		# deslocamento � direita aritm�tico
	jr $ra 			# fim do programa
