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
        lw $t1, TRISE($t0)
        andi $t1, $t1, 0xFFC1       # TRISE = (TRISE & 0xFFC1)
        sw $t1, TRISE($t0)

        li $t2, 1                   # cnt = 1

while:  lw $t1, LATE($t0)
        sll $t3, $t2, 1             # cnt << 1
        andi $t1, $t1, 0xFFC1       # LATE = LATE & 0xFFC1
        or $t1, $t1, $t3            # LATE = (LATE & 0xFFC1) | (cnt << 1)
        sw $t1, LATE(t0)

        move $a0, $t2               
        li $a1, 0x00050002
        li $v0, printInt            
        syscall                     # printInt(cnt, 2 | 5 << 16)

        la $a0, '\n'
        li $v0, putChar
        syscall                     # putChar('\n')

        beq $t2, 16, rst_cnt        # if(cnt == 16)
        sll $t2, $t2, 1             # cnt << 1

        j end_w

rst_cnt:
        li $t2, 1                   # cnt = 1

end_w:  jal delay
        j while

delay:  li $v0, resetCoreTimer
        syscall

loop:   li $v0, readCoreTimer
        syscall
        blt $v0, 8695652, loop

        jr $ra


