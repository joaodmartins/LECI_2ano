#include <detpic32>

void puts(char *str) {
    while(*str != '0') {
        putc(*str);
        str++;
    }
}

void putc(char byte) {
    while(U2STAbits.UTXBF);
    U2TXREG = byte;
}


int main(void) {
    U2MODEbits.BRGH = 0;
    U2MODEbits.PDSEL = 2;
    U2MODEbits.STSEL = 1;
    U2STAbits.URXEN = 1;
    U2STAbits.UTXEN = 1;
    U2MODEbits.ON = 1;

    IEC1bits.U2RXIE = 1;
    IEC1bits.U2TXIE = 0;

    IPC8bits.U2IP = 1;

    IFS1bits.U2RXIF = 0;

    U2STAbits.URXISEL = 0;

    EnableInterrupts();

}

void _int_(32) isr_uart2(void) {
    if(IFS1bits.U2RXIF) {
        char byte = U2RXREG;
        putc(byte);
        if (byte == 'C') {
            
        }
    }
}