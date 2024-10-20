	.data
	.text
	.globl main
main: 	#1c)	0x0F1E - 3870
	#	0x0614 - 1556
	#	0xE543 - 58691
	ori $v0,$0,5 #
	syscall 		# chamada ao syscall "read_int()"
	or $t0,$0,$v0 		# $t0 = $v0 = valor lido do teclado
		
	xori $t1,$t0,0xffffffff # $t2 = $t0 & $t1 (and bit a bit)
	
	or $a0,$0,$t1 		
	ori $v0,$0,34 		# 
	syscall 		# chamada ao syscall "print_int16()"
	
	jr $ra # fim do programa
