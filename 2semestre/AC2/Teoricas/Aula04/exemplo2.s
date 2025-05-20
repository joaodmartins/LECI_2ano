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

        .text 
        .globl main

main:   lui $t0, ADDR_BASE_HI   # 16 MSbits of port addresses
        lw $t1, TRISD($t0)      # Read TRISD register
        andi $t1, $t1, 0xFFFE   # Modify bit 0 (0 is OUT)
        sw $t1, TRISD($t0)      # Write TRISD (port configured)

loop:   lw $t1, LATD($t0)       # Read LATD
        ori $t1, $t1, 0x0001    # Modify bit 0 (set)
        sw $t1, LATD($t0)       # Write LATD

        li $a0, 100 
        jal delay               # wait 100 ms

        lw $t1, LATD($t0)       # Read LATD
        andi $t1, $t1, 0xFFFE   # Modify bit 0 (reset)
        sw $t1, LATD($t0)       # Write LATD

        li $a0, 900             
        jal delay               # wait 900ms

        j loop

delay:  li $v0, RESET_CORE_TIMER
        syscall

        li $t2, 20000
        mul $t2, $a0, $t2

while:  li $v0, READ_CORE_TIMER
        syscall
        blt $v0, $t2, while

        jr $ra 
    