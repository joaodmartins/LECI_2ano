	.data
	.text
	.globl main
main: 	#1a)
	ori $v0,$0,5 #
	syscall 		# chamada ao syscall "read_int()"
	or $t6,$0,$v0 		# $t0 = $v0 = valor lido do teclado
	
	ori $v0,$0,5 #
	syscall 		# chamada ao syscall "read_int()"
	or $t7,$0,$v0 		# $t0 = $v0 = valor lido do teclado
	
	or $t0,$0,$t6 # substituir val_1 e val_2 pelos
	or $t1,$0,$t7 # valores de entrada desejados
	
	#1b) 		hex	dec10		hex	dec10
	#	val_1 = 0x1234 - 4660, val_2 = 0x000F - 15
	#	val_1 = 0x1234 - 4660, val_2 = 0xF0F0 - 61680
	#	val_1 = 0x5C1B - 23579, val_2 = 0xA3E4 - 41956
		
	
	and $t2,$t0,$t1 # $t2 = $t0 & $t1 (and bit a bit)
	or $t3,$t0,$t1 # $t3 = $t0 | $t1 (or bit a bit)
	nor $t4,$t0,$t1 #$t4 = $t0 NOR $t1 (or bit a bit)
	xor $t5,$t0,$t1 # $t3 = $t0 XOR $t1 (or bit a bit)
	
	or $a0,$0,$t2 		
	ori $v0,$0,34 		# 
	syscall 		# chamada ao syscall "print_int16()"
	
	or $a0,$0,$t3 		
	ori $v0,$0,34 		# 
	syscall 		# chamada ao syscall "print_int16()"
	
	or $a0,$0,$t4 		
	ori $v0,$0,34 		# 
	syscall 		# chamada ao syscall "print_int16()"
	
	or $a0,$0,$t5 		
	ori $v0,$0,34 		# 
	syscall 		# chamada ao syscall "print_int16()"
	
	jr $ra # fim do programa
