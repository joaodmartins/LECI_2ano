	.data
	.text
	.globl main
main: 	#2e)
	li $t0,0xff 	# instru��o virtual (decomposta ### n� em gray
				# em duas instru��es nativas)
	
	or $t1,$t0,$0		#num = gray;
	
	srl $t3,$t1,4 		# num = num ^ (num >> 4); 
	xor $t1,$t1,$t3		# num=$t1  
	
	srl $t3,$t1,2 		# num = num ^ (num >> 2); 
	xor $t1,$t1,$t3		# num=$t1  
	
	srl $t3,$t1,1 		# num = num ^ (num >> 1); 
	xor $t1,$t1,$t3		# num=$t1  
	
	or $t2,$t1,$0 		#bin = num; 
	
	
	jr $ra 			# fim do programa
	
	#isso est� a fzr o que � pedido em c++ mas quando fa�o manualmente parece que est� mal WTF???
