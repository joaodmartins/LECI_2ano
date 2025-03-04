    .equ ADDR_BASE_HI, 0xBF88
    .equ TRISB, 0x6040
    .equ PORTB, 0x6050
    .equ LATB, 0x6060

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

    # Configurar RB0 como entrada
    lw $t3, TRISB($t1)
    ori $t3, $t3, 0x0001   # Define RB0 (bit 0) como entrada
    sw $t3, TRISB($t1)

loop:   
    # Ler RB0 (PORTB)
    lw $t4, PORTB($t1)
    andi $t4, $t4, 0x0001   # Isola bit 0 (RB0)
    xori $t4, $t4, 0x0001   # Inverte bit 0 (0 -> 1, 1 -> 0)

    # Escrever o valor negado de RB0 em RE0 (LATE)
    lw $t5, LATE($t1)
    andi $t5, $t5, 0xFFFE   # Limpa bit 0 de RE0
    or   $t5, $t5, $t4      # Define bit 0 com o valor invertido de RB0
    sw   $t5, LATE($t1)     # Escreve no registrador de saída

    j loop                  # Loop infinito
    jr $ra
