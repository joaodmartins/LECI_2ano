        .equ GET_CHAR, 2
        .equ PUT_CHAR, 3
        .equ PRINT_INT, 6

        .data 
        .text 
        .globl main

main:   li $t0, 0           

dow:    li $v0, GET_CHAR
        syscall
        move $t1, $v0

        addi $t2, $t1, 1
        li $v0, PUT_CHAR
        move $a0, $t2
        syscall

        addi $t0, $t0, 1

        li $t3, 10
        beq $t1, $t3, enddw

        j dow

enddw:  li $v0, PRINT_INT
        move $a0, $t0
        li $a1, 10
        syscall

        li $v0, 0
        jr $ra