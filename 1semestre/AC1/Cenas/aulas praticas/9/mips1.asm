	.data
um:	.float 1.0
	.text
	.globl main
#######################################
main:	addiu $sp,$sp,-4	# abrir espaço na stack
       	sw $ra,0($sp)     	# salvaguardar o $ra
do:
       	li $v0,6		# read_float()
       	syscall			# $f0 = x
       	li $v0,5		# read_int()
      	syscall			# $v0 = y
       
       	mov.s $f12,$f0		# $f12 = x
       	move $a0,$v0		# $a0 = y
       	jal xtoy		# xtoy($f12,$a0)

       	li $v0,2		# print_float(res)
       	mov.s $f12,$f0		# $f12 = res 
       	syscall
       
       	mtc1 $0,$f8		# $f8 = 0.0
	
       	c.eq.s $f12,$f8		# res = 0.0
while:	bc1f do			# if !(res = 0.0) = if (res != 0.0)  
	
	li $v0,0
	
	lw $ra,0($sp)		# repor $ra
	addiu $sp,$sp,4		# repor a stack
	
	jr $ra	
#######################################

	# x=$f12
	# y=$a0 -> $s0
	# i=$s1
	# result= $f22
xtoy: addiu $sp,$sp,-20		# salvaguardar 
      sw $ra,0($sp)		# salvaguardar $ra
      s.s $f20,4($sp)		# salvaguardar $f20
      sw $s0,8($sp)		# salvaguardar $s0
      sw $s1,12($sp)		# salvaguardar $s1
      s.s $f22,16($sp)		# salvaguardar $f22
      
      mov.s $f20,$f12		# $f20 = x;
      move $s0,$a0		# $s0 = y;
      li $s1,0			# $s1 = 0 = i;
      l.s $f22,um		# $f22 = 1.0 = result;
      
for:  move $a0,$s0		# $a0 = y;
      jal abs			# abs($a0)
      
      bge $s1,$v0,endfor 	# i < abs(y)
      
if:   ble $s0,$0,else		# if(y > 0) 
      
      mul.s $f22,$f22,$f20	# $f22 = result * x <=> $f22 * $f20
      j endif
else:
      div.s $f22,$f22,$f20	# $f22 = result / x <=> $f22 / $f20
endif:
      addi $s1,$s1,1		# i++;
      j for
endfor:
      mov.s $f0,$f22		# $f0 = $f22 <=> return result;
      
      lw $ra,0($sp)		# repor $ra
      l.s $f20,4($sp)		# repor $f20
      lw $s0,8($sp)		# repor $s0
      lw $s1,12($sp)		# repor $s1
      l.s $f22,16($sp)		# repor $f22
      addiu $sp,$sp,20		# repor stack
      
      jr $ra

#######################################

abs:   bge $a0,$0,endifABS	# if(val < 0) 
       sub $a0,$0,$a0 		# val = - val <=>  $a0 = $0 - $a0
endifABS:
       move $v0,$a0		# return val <=> $v0 = $a0
       jr $ra  
