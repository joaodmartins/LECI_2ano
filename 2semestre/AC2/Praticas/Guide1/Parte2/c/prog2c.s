        .equ PRINT_STR, 8
        .equ READ_INT10, 5
        .equ READ_INT, 4
        .equ PRINT_INT10, 7
        .equ PRINT_INT, 6

        .data 
str1:   .asciiz "\nIntroduza um inteiro (sinal e módulo): "
str2:   .asciiz "\nValor em base 10 (signed): "
str3:   .asciiz "\nValor em base 2: "
str4:   .asciiz "\nValor em base 16: "
str5:   .asciiz "\nValor em base 10 (unsigned): "
str6:   .asciiz "\nValor em base 10 (unsigned), formatado: "
        .text 
        .globl main

main:   la $a0, str1
        li $v0, PRINT_STR
        syscall                 # printStr(str1)

        li $v0, READ_INT10
        syscall                 # readInt10()
        move $t0, $v0           # value = readInt10()


        la $a0, str2
        li $v0, PRINT_STR
        syscall                 # printStr(str2)

        move $a0, $t0
        li $v0, PRINT_INT10
        syscall                 # printInt10(value)


        la $a0, str3
        li $v0, PRINT_STR
        syscall                 # printStr(str3)

        move $a0, $t0
        li $a1, 2
        li $v0, PRINT_INT
        syscall                 # printInt(value, 2)


        la $a0, str4
        li $v0, PRINT_STR
        syscall                 # printStr(str4)

        move $a0, $t0
        li $a1, 16
        li $v0, PRINT_INT
        syscall                 # printInt(value, 16)


        la $a0, str5
        li $v0, PRINT_STR
        syscall                 # printStr(str5)

        move $a0, $t0
        li $a1, 10
        li $v0, PRINT_INT
        syscall                 # printInt(value, 2)


        la $a0, str6
        li $v0, PRINT_STR
        syscall                 # printStr(str6)

        move $a0, $t0
        li $a1, 0x0005000A
        li $v0, PRINT_INT
        syscall                 # printInt(value, 10 | 5 << 16)