        .equ INKEY, 1
        .equ PUT_CHAR, 3
        .equ PRINT_INT, 6

        .data
        .text
        .globl main 

main:   li $t0, 0               # cnt = 0

dow:    li $v0, INKEY
        syscall                 # inkey()
        move $t1, $v0           # c = inkey()

        beq $t1, $zero, else    # if( c != 0 )
        
        li $v0, PUT_CHAR        
        move $a0, $t1
        syscall                 # putChar( c )
        
        j endif

else:   li $v0, PUT_CHAR        
        li $a0, '.' 
        syscall                 # putChar('.')
endif:  addi $t0, $t0, 1        # cnt++

        li $t2, '\n'            
        beq $t1, $t2, enddw     # while( c != '\n')

        j dow
enddw:  li $v0, PRINT_INT       
        move $a0, $t0
        li $a1, 10  
        syscall                 # printInt(cnt, 10)

        li $v0, 0               # return 0
        jr $ra 