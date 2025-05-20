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

main:   lui $t0, ADDR_BASE_HI   # $t0 = 0xBF880000
        lw $t1, TRISB($t0)      # Address: BF880000 + 00006040
        ori $t1, $t1, 0x0004    # bit2 = 1 (IN) 
        sw $t1, TRISB($t0)      # RB2 configured as IN

        lw $t1, TRISE($t0)      # Address: BF880000 + 00006100
        andi $t1, $t1, 0xFFFB   # bit2 = 0 (out)
        sw $t1, TRISE($t0)      # RE2 configured as OUT

loop:   lw $t1, PORTB($t0)      # Address: BF880000 + 00006050
        andi $t1, $t1, 0x0004   # Reset all bits except bit 2

        lw $t2, LATE($t0)       # Address: BF880000 + 00006120
        andi $t2, $t2, 0xFFFB   # Reset bit 2
        or $t2, $t2, $t1        # Merge data
        sw $t2, LATE($t0)       # Write LATE register

        j loop
