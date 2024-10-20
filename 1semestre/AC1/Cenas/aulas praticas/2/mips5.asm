	.data
	.text
	.globl main
main: 	#2e)
	li $t0,0xff 	# instrução virtual (decomposta ### nº em gray
				# em duas instruções nativas)
	
	or $t1,$t0,$0		#num = gray;
	
	srl $t3,$t1,4 		# num = num ^ (num >> 4); 
	xor $t1,$t1,$t3		# num=$t1  
	
	srl $t3,$t1,2 		# num = num ^ (num >> 2); 
	xor $t1,$t1,$t3		# num=$t1  
	
	srl $t3,$t1,1 		# num = num ^ (num >> 1); 
	xor $t1,$t1,$t3		# num=$t1  
	
	or $t2,$t1,$0 		#bin = num; 
	
	
	jr $ra 			# fim do programa
	
	#isso está a fzr o que é pedido em c++ mas quando faço manualmente parece que está mal WTF???
