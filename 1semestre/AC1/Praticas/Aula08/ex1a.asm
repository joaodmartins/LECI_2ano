	.data
	.eqv print_string, 4
	.eqv read_string, 8
	.eqv read_int,  5
	
str1: 	.space 102
str2: 	.space 52
str3:	.asciiz "Enter a string: "
str4:	.asciiz "Enter a string to insert: "
str5:	.asciiz "Enter the position: "
str6:	.asciiz "Original string: "
str7:	.asciiz "\nModified string: "
str8:	.asciiz "\n"

	.text
	.globl main
	
strlen: li $t1, 0		# len = 0
	
while: 	lb $t0, 0($a0)		
	addiu $a0, $a0, 1
	beq $t0, '\0', endw	# while(*s++ != '\0')
	addi $t1, $t1, 1	# len++
	j while	
	
endw: 	move $v0, $t1		# return len
	jr $ra
	
div:	move $t0, $a0          # $t0 = dividendo
   	move $t1, $a1          # $t1 = divisor
   	li $t2, 0              # $t2 = quociente
   	li $t3, 0              # $t3 = resto
   	
   	sll $t1, $t1, 16 	# divisor = divisor << 16
   	andi $t0, $t0, 0xFFFF	# dividendo = (dividendo & 0xFFFF)
   	sll $t0, $t0, 1		# dividendo = (dividendo & 0xFFFF) << 1
   	
for: 	li $t4, 0		# i = 0
	bge $t4, 16, endfor	# while(i < 16) {
	
	li $t5, 0		# bit = 0

if: 	blt $t0, $t1, endif 	# if(dividendo >= divisor) {

	sub $t0, $t0, $t1	# dividendo = dividendo - divisor
	li $t5, 1		# bit = 1
	
endif:	sll $t0, $t0, 1		# dividendo = (dividendo << 1)
	or $t0, $t0, $t5	# dividendo = (dividendo << 1) | bit
	
	addi $t4, $t4, 1	# i++
	j for			
	
endfor:	srl $t3, $t0, 1		# resto = (dividendo >> 1)
	andi $t3, $t3, 0xFFFF0000 	# resto = (dividendo >> 1) & 0xFFFF0000
	
	andi $t2, $t0, 0xFFFF	# quocioente = dividendo & 0xFFFF
	
	or $v0, $t3, $t2 	# return (resto | quociente)
	
	jr $ra
	
insert: move $t0, $a0		# $t0 = dst
	move $t1, $a1		# $t1 = src
	move $t2, $a2		# $t2 = pos
	
	move $a0, $t0		
	jal strlen
	move $t3, $v0		# len_dst = strlen(dst)
	
	move $a0, $t1
	jal strlen 		
	move $t4, $v0		# len_src = strlen(src)
	
if1:	bgt $t2, $t3, endif 	# if(pos <= len_dst) 

for: 	move $t5, $t3		# i = len_dst
	blt $t5, $t2, endfor	# while(i >= pos)
main:	
	