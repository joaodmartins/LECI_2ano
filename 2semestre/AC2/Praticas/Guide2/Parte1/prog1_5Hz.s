        .equ READ_CORE_TIMER, 11
        .equ RESET_CORE_TIMER, 12
        .equ PUT_CHAR, 3
        .equ PRINT_INT, 6
        .data
        .text 
        .globl main

main:   li $t0, 0

while:  li $a0, '\r'
        li $v0, PUT_CHAR
        syscall

        move $a0, $t0
        li $a1, 0x0004000A
        li $v0, PRINT_INT
        syscall

        li $v0, RESET_CORE_TIMER
        syscall

wait_loop:
        li $v0, READ_CORE_TIMER
        syscall
        li $t1, 4000000
        bge $v0, $t1, end_wait

        j wait_loop

end_wait:   
        addi $t0, $t0, 1

        j while

        li $v0, 0
        jr $ra