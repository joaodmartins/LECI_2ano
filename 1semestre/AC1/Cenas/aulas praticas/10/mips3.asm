	.data
	
	.align 2
st_array:.space 176		# 44*4=176
media:	.space 4
		
	.eqv print_str, 4
	.eqv print_int10, 1
	.eqv print_float, 2
	.eqv read_int,5
	.eqv read_str,8
	.eqv read_float,6
	.eqv print_intu10,36
	
str1:	.asciiz "\nMedia: "
str2:	.asciiz "N. Mec: "
str3:	.asciiz "Primeiro Nome: "
str4:	.asciiz "Ultimo Nome: "		
str5:	.asciiz "Nota: "	
												
	.text
	.globl main

main:	addiu $sp,$sp,-8	# salvaguardar
      	sw $ra,0($sp)
      	sw $s0,-4($sp)
      	
      	la $a0,st_array
      	li $a1,4
      	jal read_data		# read_data( st_array, MAX_STUDENTS ); 
      	
      	la $a0,st_array
      	li $a1,4
      	la $a2,media		#  &media == endereço da media 
      	jal max
      	move $s0,$v0		# pmax = max( st_array, MAX_STUDENTS, &media );
      	
      	li $v0,print_str
      	la $a0,str1
      	syscall			# print_str("\nMedia: "); 
      	
      	la $s1,media
   	l.s $f12,0($s1)
	li $v0,print_float
	syscall 		# print_float( media ); 
	
	move $a0,$s0
	jal print_student	# print_student( pmax ); 
	
	lw $ra,0($sp)
      	lw $s0,4($sp)
      	addiu $sp,$sp,8		# repor
      	
      	jr $ra
      	
read_data:			# sub-rotina terminal 
	move $t0,$a0		# $t0= student *st
	move $t1,$a1		# $t1= ns
	li $t2,0		# i=0
	
for_read:bge $t2,$t1,endf_read	# for(i=0; i < ns; i++) {
      	
      	li $v0,print_str
      	la $a0,str2
      	syscall			# print_str("N. Mec: "); 
      	
      	li $v0,read_int
      	syscall			# read_int();
      	
      	mul $t3,$t2,44		
      	addu $t3,$t3,$t0	# $t3=st[i]  	
      	sw $v0,0($t3)		# st[i].id_number = read_int(); 
      	
      	li $v0,print_str
      	la $a0,str3
      	syscall			# print_str("Primeiro Nome: "); 
      	
      	addiu $a0,$t3,4	
      	li $a1,18
      	li $v0,read_str
      	syscall			# read_str(st[i].first_name, 18); 
      	
      	li $v0,print_str
      	la $a0,str4
      	syscall			# print_str("Ultimo Nome: "); 
      	
      	addiu $a0,$t3,22	
      	li $a1,15
      	li $v0,read_str
      	syscall			# read_str(st[i].last_name, 15); 
      	
      	li $v0,print_str
      	la $a0,str5
      	syscall			# print_str("Nota: ");
      	
      	li $v0,read_float
      	syscall			# read_float();
      		
      	s.s $f0,40($t3)		# st[i].grade = read_float(); 
      	
      	addi $t2,$t2,1 		# i++
      	j for_read		#}
endf_read:
	jr $ra
	
max:				# sub-rotina terminal 
	move $t0,$a0		# $t0= student *st
	move $t1,$a1		# $t1= ns
	move $t2,$a2		# $t2= float *media -> ponteiro
	
	
	li $t4,-20
	mtc1 $t4,$f2		
	cvt.s.w $f2,$f2		# $f1 = -20.0	$f2=max_grade
	
	mtc1 $0,$f4		
	cvt.s.w $f4,$f4		# $f4 = 0.0	$f4=sum
		
#########################################################
#							#
# utilização por ponteiros, logo o p++ = +44		#
# ent o p<(st + ns) o ns tem de ser ns*44 nao é???	#
#							#
#########################################################

	move $t3,$t0		# p = st	$t3=p
	
	mul $t4,$t1,44		## por ser por ponteiros
	add $t5,$t0,$t4		# $t5=(st + ns)
for_max:bge $t3,$t5,endf_max

	l.s $f6,40($t3)		# p->grade; 
	add.s $f4,$f4,$f6	# sum += p->grade; 
	
	c.le.s $f6,$f2		
if_max:	bc1t end_if_max		# if(p->grade > max_grade) 
	
	mov.s $f2,$f6 		# max_grade = p->grade; 
	move $t6,$t3		# pmax = p; 
	
end_if_max:			#}
	
	addiu $t3,$t3,44	# p++
	j for_max
endf_max:			#}

	mtc1 $t1,$f8		
	cvt.s.w $f8,$f8		# (float)ns
	div.s $f10,$f4,$f8	# $f10= sum / (float)ns;
	s.s $f10,0($t2)		# *media = sum / (float)ns; 
	
	move $v0,$t6		# return pmax; 
	
	jr $ra

print_student:			# sub-rotina terminal 
	move $t1,$a0		# $t1=p
	
	li $a0,'\n'		# EXTRA para ler melhor
	li $v0,11		# EXTRA para ler melhor
	syscall			# EXTRA para ler melhor
	
	lw $a0,0($t1)		# p->id_number
	li $v0,print_intu10
	syscall			# print_intu10(p->id_number); 
	
	li $a0,'\n'		# EXTRA para ler melhor
	li $v0,11		# EXTRA para ler melhor
	syscall			# EXTRA para ler melhor
	
	addiu $a0,$t1,4		# p->first_name
	li $v0,print_str
	syscall			# print_str(p->first_name); 

	li $a0,'\n'		# EXTRA para ler melhor
	li $v0,11		# EXTRA para ler melhor
	syscall			# EXTRA para ler melhor
	
	addiu $a0,$t1,22	# p->last_name
	li $v0,print_str
	syscall			# print_str(p->last_name); 

	li $a0,'\n'		# EXTRA para ler melhor
	li $v0,11		# EXTRA para ler melhor
	syscall			# EXTRA para ler melhor
	
	l.s $f12,40($t1)		# p->grade
	li $v0,print_float
	syscall			# print_float(p->grade); 
	
	jr $ra
      	
