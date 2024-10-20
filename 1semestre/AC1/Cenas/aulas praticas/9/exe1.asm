#
# int main(void)
# {
# 	float x;
# 	int y;
# 	float result;
# 
# 	do
# 	{
#  	x = read_float();
#  	y = read_int();
#  	res = xtoy(x,y);
#  	print_float(res); 
#
# 	}while(res != 0.0);
#
# 	return 0;
# }
#
#
	.data
um:	.float 1.0
	.text

xtoy: addiu $sp,$sp,-20
      sw $ra,0($sp)
      s.s $f20,4($sp)
      sw $s0,8($sp)
      sw $s1,12($sp)
      s.s $f22,16($sp)
      
      mov.s $f20,$f12	# $f20 = x;
      move $s0,$a0	# $s0 = y;
      li $s1,0		# $s1 = 0 = i;
      l.s $f22,um	# $f22 = 1.0 = result;
      
for:  move $a0,$s0	# $a0 = y;
      jal abs
      
      bge $s1,$v0,endfor # i < abs(y)
      
if:   ble $s0,$0,else
      
      mul.s $f22,$f22,$f20	# $f22 = result * x <=> $f22 * $f20
      j endif
else:
      div.s $f22,$f22,$f20	# $f22 = result / x <=> $f22 / $f20
endif:
      addi $s1,$s1,1	# i++;
      j for
endfor:
      mov.s $f0,$f22	# $f0 = $f22 <=> return result;
      
      lw $ra,0($sp)
      l.s $f20,4($sp)
      lw $s0,8($sp)
      lw $s1,12($sp)
      l.s $f22,16($sp)
      addiu $sp,$sp,20
      
      jr $ra
      
abs:

ifABS: bge $a0,$0,endifABS
       sub $a0,$0,$a0 	# val = - val <=>  $a0 = $0 - $a0
endifABS:
       move $v0,$a0	# return val <=> $v0 = $a0
       jr $ra      
    
    
	.globl main
main:
       addiu $sp,$sp,-4
       sw $ra,0($sp)
       
do:
       li $v0,6		# read_float()
       syscall		# $f0 = x
       li $v0,5		# read_int()
       syscall		# $v0 = y
       
       mov.s $f12,$f0	# $f12 = x
       move $a0,$v0	# $a0 = y
       jal xtoy

       li $v0,2		# print_float(res)
       mov.s $f12,$f0	# $f12 = res 
       syscall
       
       mtc1 $0,$f8	# $f8 = 0.0
	
       c.eq.s $f12,$f8		# res = 0.0
while:	bc1f do		# if !(res = 0.0) = if (res != 0.0)  
	
	li $v0,0
	
	lw $ra,0($sp)
	addiu $sp,$sp,4
	
	jr $ra