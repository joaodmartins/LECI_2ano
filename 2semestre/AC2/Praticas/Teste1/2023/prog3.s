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

main:   
    li $t3, 0                   # counter = 0
    lui $t0, ADDR_BASE_HI
    lw $t1, TRISE($t0)
    andi $t1, $t1, 0xFF83       # RE6 a RE2 saida
    sw $t1, TRISE($t0) 

while:
    lw $t2, LATE($t0)
    sll $t4, $t3, 2             # counter << 2
    andi $t2, $t2, 0xFF83       # LATE = LATE & 0xFF83
    or $t2, $t2, $t4            # LATE = (LATE & 0xFF83) | (counter << 2)       
    sw $t2, LATE($t0)

    move $a0, $t3
    li $a1, 0x00050002
    li $v0, printInt
    syscall

    la $a0, '\n'
    li $v0, putChar
    syscall

    addi $t3, $t3, -1           # counter - 1
    blt $t3, 0, lower           # if counter < 0 go to lower

end_w:
    jal delay
    j while

lower: 
    li $t3, 24
    j end_w
delay:
    li $v0, resetCoreTimer
    syscall

loop:
    li $v0, readCoreTimer
    syscall
    blt $v0, 4347826, loop

    jr $ra


