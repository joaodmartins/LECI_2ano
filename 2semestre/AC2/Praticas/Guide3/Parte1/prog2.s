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
    .globl main
    .text 

main:   
    lui $t1, ADDR_BASE_HI
    lw  $t2, TRISE($t1)
    andi $t2, $t2, 0xFFFE
    sw $t2, TRISE($t1)

    lw $t3, TRISB($t1)
    ori $t3, $t3, 0x0001
    sw $t3, TRISB($t1)

loop:   
    lw $t4, PORTB($t1)
    andi $t4, $t4, 0x0001 
    xori $t4, $t4, 0x0001
    
    lw $t5, LATE($t1)
    andi $t5, $t5, 0xFFFE
    or   $t5, $t5, $t4
    
    sw $t5, LATE($t1)
    
    j loop
    jr $ra