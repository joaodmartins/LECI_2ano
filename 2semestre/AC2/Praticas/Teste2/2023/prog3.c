#include <detpic32.h>

volatile int count = 0;

int main(void) {
    TRISE = (TRISE & 0xFFF0); // Configure RE0-RE3 as outputs
    LATE = (LATE& 0xFFF0) | count;

    U2BRG = ((20000000 + 8 * 2400) / (16 * 2400)) - 1;

    U2MODEbits.BRGH = 0;
    U2MODEbits.PDSEL = 3;  // even parity
    U2MODEbits.STSEL = 1;  // 2 bits to stop
    U2STAbits.URXEN = 1; // Enable receiver
    U2STAbits.UTXEN = 1; // Enable transmitter

    // enable U2RXIE disable U2TXIE (register IEC1)
    IEC1bits.U2RXIE = 1;
    IEC1bits.U2TXIE = 0;
    // Set UART2 priority level (register IEC1)
    IPC8bits.U2IP = 1;
    // clear Interrupt Flag bit U2RXIF (register IFS1)
    IFS1bits.U2RXIF = 0;
    // define RX interrupt mode (URXISEL bits)
    U2STAbits.URXISEL = 0;  // has 1 character

    EnableInterrupts();

    count = 0;

    while(1){
        IdleMode(); // Enter idle mode to save power
    }
    return 0;
}

void _int_(32) isr_uart2(void) {
    if(IFS1bits.U2RXIF == 1) {
        char byte = U2RXREG; 
        if(byte == 'F') {
            count++;   
            if(count == 10) {
                count = 0;
            }     
        }
        if(byte == 'C') {
            count = 0;
            puts("VALOR MINIMO\n");
        }
        LATE = (LATE & 0xFFF0) | count;
        IFS1bits.U2RXIF = 0;
    }
}

void puts(char *str) {
    while(*str != '\0') {
        putc(*str);
        str++;
    }
}

void putc(char byte) {
    while(U2STAbits.UTXBF); // Wait while UTXBF is set
    U2TXREG = byte; // Write character to transmit register
}


