	.data
	
	.eqv print_float, 2
	.eqv print_string, 4
	.eqv read_int, 5
	.eqv read_float, 6

str1: 	.asciiz "Introduza a base: "
str2:	.asciiz "Introduza o expoente: "
str3: 	.asciiz "O resultado e': "
						
k0: 	.float 1.0
k1: 	.float 1.0
k2: 	.float 0.0

	.text
	.globl main
	
abs:	
# Mapa de registos
# val -> $a0
	move $v0, $a0
if: 	bgez $a0, endif
	sub $v0, $0, $a0				
endif: 	jr $ra

#----------------------------------------------------------------------------

xtoy: 	
# Mapa de registos
# x -> 	$f12: $f20
# y -> 	$a0: 	$s0	
# i:  	$s1
# result: $f22

	addiu $sp, $sp, -20
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	sw $s1, 8($sp)
	s.s $f20, 12($sp)
	s.s $f22, 16($sp)
	
	la $t0, k0
	l.s $f22, 0($t0)
	move $s0, $a0 
	
	jal abs
	move $t2, $v0
	
for:	bge $s1, $t2, endfor
	
	blez $s0, else
	mul.s $f22, $f22, $f20 
	j endif1
	
else:
	div.s $f22, $f22, $f20 
	
endif1:
	addi $s1, $s1, 1
	j for
	
endfor: 
	mov.s $f0, $f22
	
	l.s $f22, 16($sp)
	l.s $f20, 12($sp)
	lw $s1, 8($sp)
	lw $s0, 4($sp)
	lw $ra, 0($sp)
	addiu $sp, $sp, 20
 	
 	jr $ra
 		
#---------------------------------------------------------------------------	
sqrt: 	
# Mapa de registos
# val: 	$f12
# aux: 	$f2
# xn: 	$f4
# i: 	$t0

	la $t1, k1
	l.d $f4, 0($t1) 	# xn = 1.0
	
	li $t0, 0		# i = 0
	
if: 	la $t1, k2		
	l.d $f6, 0($t1)
	c.le.d $f12, $f6
	bclt else
	
do: 	c.eq.d $f2, $f4
	bc1f enddo
	
enddo: 	
	
	j endif
	
else: 	mov.d $f4, $f6

endif: 
	mov.d $f0, $f4
	jr $ra

#---------------------------------------------------------------------------
main: 	addiu $sp, $sp, -4
	sw $ra, 0($sp)
	
	li $v0, print_string
	la $a0, str1
	syscall
	
	li $v0, read_float
	syscall
	mov.s $f12, $f0
	
	li $v0, print_string
	la $a0, str2
	syscall
	
	li $v0, read_int
	syscall
	move $a0, $v0
	
	jal xtoy
	mov.s $f12, $f0
	
	li $v0, print_string
	la $a0, str3
	syscall
	
	li $v0, print_float
	syscall
	
	lw $ra, 0($sp)
	addiu $sp, $sp, 4
	jr $ra
