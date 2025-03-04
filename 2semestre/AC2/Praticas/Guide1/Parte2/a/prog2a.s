        .equ GET_CHAR, 2
        .equ PUT_CHAR, 3
        .equ PRINT_INT, 6

        .data 
        .text 
        .globl main

main:   li $t0, 0               # cnt = 0

dow:    li $v0, GET_CHAR        
        syscall                 # getChar()
        move $t1, $v0           # c = getChar()

        li $v0, PUT_CHAR        
        move $a0, $t1
        syscall                 # putChar(c)

        addi $t0, $t0, 1        # cnt++

        li $t2, 10              # $t2 = '\n'
        beq $t1, $t2, enddw     # while c != '\n'

        j dow       

enddw:  li $v0, PRINT_INT
        move $a0, $t0
        li $a1, 10
        syscall                 # printInt(cnt, 10)

        li $v0, 0               # return
        jr $ra