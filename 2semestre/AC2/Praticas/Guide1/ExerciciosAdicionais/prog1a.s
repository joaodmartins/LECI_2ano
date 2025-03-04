        .equ UP, 1
        .equ DOWN, 0
        .equ PUT_CHAR, 3
        .equ PRINT_INT, 6
        .equ INKEY, 1

        .data 
        .text 
        .globl main

main:   li $t0, 0           # state = 0
        li $t1, 0           # cnt = 0

dow:    li $a0, '\r'
        li $v0, PUT_CHAR
        syscall             # putChar('\r')

        move $a0, $t1
        li $a1, 0x0003000A
        li $v0, PRINT_INT
        syscall             # printInt( cnt, 10 | 3 << 16 )

        li $a0, '\t'
        li $v0, PUT_CHAR
        syscall             # putChar('\t')

        move $a0, $t1
        li $a1, 0x00080002
        li $v0, PRINT_INT
        syscall             # printInt( cnt, 2 | 8 << 16 )

        li $a0, 5
        jal wait            # wait(5)

        li $v0, INKEY 
        syscall             # inkey()
        move $t2, $v0       # c = inkey()

        li $t3, '+'
        bne $t2, $t3, check_minus # if( c == '+' )
        li $t0, UP          # state = UP

check_minus:  
        li $t3, '-'
        bne $t2, $t3, update_cnt # if( c == '-' )
        li $t0, DOWN        # state = DOWN

update_cnt:  
        bne $t0, UP, check_down  # if( state == UP )
        addi $t1, $t1, 1    # cnt = (cnt + 1)
        andi $t1, $t1, 0xFF # cnt = (cnt + 1) & 0xFF
        j dowf

check_down:  
        bne $t0, DOWN, dowf # if( state == DOWN )
        addi $t1, $t1, -1   # cnt = (cnt - 1)
        andi $t1, $t1, 0xFF # cnt = (cnt - 1) & 0xFF

dowf:   li $t3, 'q'
        beq $t2, $t3, enddw # while( c != 'q' )

        j dow               

enddw:  li $v0, 0           # return 0
        jr $ra

wait:   li $t4, 0           # i = 0 
        li $t5, 515         # Parte alta de 515000
        li $t6, 1000        # Parte baixa de 515000
        mul $t5, $t5, $t6   # $t5 = 515 * 1000 = 515000
        mul $t6, $a0, $t5   # $t6 = 515000 * ts

wait_loop:  
        bge $t4, $t6, endwait   # while ( i < 515000 * ts )
        addi $t4, $t4, 1        # i++

        j wait_loop

endwait:    
        jr $ra  
 
        
