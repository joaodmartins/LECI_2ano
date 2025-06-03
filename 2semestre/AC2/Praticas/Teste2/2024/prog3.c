#include <detpic32.h>

void puts(char *str) {
    while(*str != '\0') {
        putc(*str);
        str++;
    }
}

void putc(char byte) {
    while(U2STAbits.UTXBF);
    U2TXREG = byte;
}

int main(void) {
    TRISE = (TRISE & 0xFF7F);
    TRISB = (TRISB & 0xFFF0);

    U2BRG = ((20000000 + (8 * 9600)) / (16 * 9600)) - 1;

    U2MODEbits.BRGH = 0;
    U2MODEbits.PDSEL = 2;   // odd-parity
    U2MODEbits.STSEL = 1;   // 2 bits to stop
    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;
    U2MODEbits.ON = 1;

    IEC1bits.U2RXIE = 1;
    IEC1bits.U2TXIE = 0;

    IPC8bits.U2IP = 1;

    IFS1bits.U2RXIF = 0;

    EnableInterrupts();

    while(1) {
        IdleMode();
    }
    return 0;
}

void _int_(32) isr_uart2(void) {
    if(IFS1bits.U2RXIF) {
        char byte = U2RXREG;
        putc(byte);
        if(byte == 'D') {
            int value = PORTB & 0x000F;
            int dezenas = value / 10;
            int unidades = value % 10;
            puts("DSD=");
            putc(dezenas + '0');
            putc(unidades + '0')
        }
    }
}

