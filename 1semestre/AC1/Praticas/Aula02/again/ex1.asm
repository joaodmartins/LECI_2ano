	.data
	.text
	.globl main
main:	ori $t0, $0, 0x1234
	ori $t1, $0, 0x000F
	and $t2, $t0, $t1	# $t2 = $t0 & $t1 (and bit a bit)
	or  $t3, $t0, $t1	# %t3 = $t0 | $t1 (or bit a bit)
	nor $t4, $t0, $t1	# %t3 = ~($t0 | $t1) (nor bit a bit)
	xor $t5, $t0, $t1	# %t3 = $t0 ^ $t1 (xor bit a bit)
	
	or $a0, $0, $t2
	ori $v0, $0, 34
	syscall
	
	or $a0, $0, $t3
	ori $v0, $0, 34
	syscall
	
	or $a0, $0, $t4
	ori $v0, $0, 34
	syscall
	
	or $a0, $0, $t5
	ori $v0, $0, 34
	syscall
	
	jr $ra