    .equ ADDR_BASE_HI, 0xBF88
    .equ TRISD, 0x60C0
    .equ PORTD, 0x60D0

    .equ TRISE, 0x6100
    .equ PORTE, 0x6110
    .equ LATE, 0x6120

    .data 
    .globl main
    .text 

main:   
    lui $t1, ADDR_BASE_HI

    # Configurar RE0 como saída
    lw  $t2, TRISE($t1)
    andi $t2, $t2, 0xFFFE   # Define RE0 (bit 0) como saída
    sw $t2, TRISE($t1)

    # Configurar RD8 como entrada
    lw $t3, TRISD($t1)
    ori $t3, $t3, 0x0100   # Define RD8 (bit 8) como entrada (bit 8 = 1)
    sw $t3, TRISD($t1)

loop:   
    # Ler RD8 (PORTD)
    lw $t4, PORTD($t1)
    andi $t4, $t4, 0x0100   # Isola bit 8 (RD8)
    srl  $t4, $t4, 8       # Desloca bit 8 para a posição 0

    # Escrever o valor de RD8 em RE0 (LATE)
    lw $t5, LATE($t1)
    andi $t5, $t5, 0xFFFE   # Limpa bit 0 de RE0
    or   $t5, $t5, $t4      # Define bit 0 com o valor de RD8
    sw   $t5, LATE($t1)     # Escreve no registrador de saída

    j loop                  # Loop infinito
    jr $ra
