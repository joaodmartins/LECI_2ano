        .equ SIZE, 20
        .equ PRINT_STR, 8
        .equ READ_STR, 9
        .equ PRINT_INT, 6
        .equ PRINT_INT10, 7

        .data 

str1:   .space 21
str2:   .space 21

str3:   .space 41
msg1:   .asciiz "Introduza 2 strings: "
msg2:   .asciiz "Resultados:\n"

        .text
        .globl main

main:   la $a0, msg1
        li $v0, PRINT_STR
        syscall

        la $a0, str1
        li $a1, SIZE
        li $v0, READ_STR
        syscall

        la $a0, str2
        li $a1, SIZE
        li $v0, READ_STR
        syscall

        la $a0, msg2
        li $v0, PRINT_STR
        syscall

        la $a0, str1
        jal strlen
        move $a0, $v0
        li $a1, 10
        li $v0, PRINT_INT
        syscall

        la $a0, str2
        jal strlen
        move $a0, $v0
        li $a1, 10
        li $v0, PRINT_INT
        syscall



        li $v0, 0               # return 0
        jr $ra

strlen: move $t0, $a0
        li $v0, 0               # len = 0

for_strlen:  
        lb $t1,0($t0)
        beq $t1, $zero, end_for_loop
        addi $v0, $v0, 1
        addi $t0, $t0, 1

        j for_loop

end_strlen:
        jr $ra

strcpy: move $t0, $a0
        move $t1, $a1

for_strcpy: 
        lb $t2, 0($t1)
        sb $t2, 0($t0)
        beq $t2, $zero, end_strcpy
        addi $t0, $t0, 1 
        addi $t1, $t1, 1
        
        j for_strcpy

end_strcpy:
        move $v0, $a0
        jr $ra

strcat: move $t0, $a0 
        move $t1, $a1

for_strcat:     
        
