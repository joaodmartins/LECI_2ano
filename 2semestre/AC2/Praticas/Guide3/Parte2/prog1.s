    .equ READ_CORE_TIMER, 11
    .equ RESET_CORE_TIMER, 12
    
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
    lui $t0, ADDR_BASE_HI

    lw $t1, TRISE($t0)
    andi $t1, $t1, 0xFFE1
    sw $t1, TRISE($t0)
    lw $t1, TRSB($t0)
    ori $t1, $t1, 0x000F
    sw $t1, TRISB($t0)

    li $t2, 0

    lw $t1, LATE($t0)
    andi $t1, 0xFFE1
    sll $t3, $t2, 1
    or $t1, $t1, $t3
    sw $t1, LATE($t0)

    li $v0, RESET_CORE_TIMER
    syscall

wait:  
    li $v0, READ_CORE_TIMER
    syscall
    blt $v0, 4347826, wait

    