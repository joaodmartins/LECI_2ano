	.data
	.text
	.globl main
main: 	#2d)
	li $t0,4 	# instrução virtual (decomposta
				# em duas instruções nativas)

	srl $t2,$t0,1 		# gray = bin ^ (bin >> 1); 
	xor $t1,$t0,$t2		# gray=$t1   bin=$t0
	
	jr $ra 			# fim do programa
