        .equ ADDR_BASE_HI, 0xBF88

        .equ TRISB, 0x6040
        .equ PORTB, 0x6050
        .equ LATB, 0x6060

        .equ TRISC, 0x6080
        .equ PORTC, 0x6090
        .equ LATC, 0x60A0

        .equ TRISD, 0x60C0
        .equ PORTD, 0x60D0
        .equ LATD, 0x60E0

        .equ TRISE, 0x6100
        .equ PORTE, 0x6110
        .equ LATE, 0x6120

        .data 

        .text 
        .globl main

main:   lui $t0, ADDR_BASE_HI 
        lw $t1, TRISE($t0)
        andi $t1, $t1, 0xFFF0
        sw $t1, TRISE($t0)

        
