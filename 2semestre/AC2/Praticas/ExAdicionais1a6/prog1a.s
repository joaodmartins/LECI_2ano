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

        .equ putChar, 3
        .equ readInt, 5
        .equ printStr, 8
        .equ readCoreTimer, 11
        .equ resetCoreTimer, 12

        .data 
        .globl main
        .text 

main:   lui $t0, ADDR_BASE_HI
        # SET RB3 ... RB0 AS INPUT
        lw $t1, TRISB($t0)
        ori $t1, $t1, 0x000F
        sw $t1, TRISB($t0)
        # SET RE3 ... RE0 AS OUTPUT
        lw $t1, TRISE($t0)
        andi $t1, $t1, 0xFFF0
        sw $t1, TRISE($t0)

while:  lw $t2, PORTB($t0)
        andi $t3, $t2, 0x000F

        lw $t4, LATE($t0)
        andi $t4, $t4, 0xFFF0
        or $t4, $t4, $t3
        sw $t4, LATE($t0)
