#include <detpic32.h>

volatile int count = 0;

int main(void) {
    TRISE = (TRISE & 0xFFE1); // Configure RE1-RE4 as outputs
    LATE = (LATE & 0xFFE1) | (count << 1);

    U2BRG = ((20000000 + 8 * 9600) / (16 * 9600)) - 1;

    U2MODEbits.BRGH = 0;
    U2MODEbits.PDSEL = 0;  // 8-bit data, even parity, 1 stop bit
    U2MODEbits.STSEL = 0;  // 1 stop bit
    U2STAbits.URXEN = 1; // Enable receiver
    U2STAbits.UTXEN = 1; // Enable transmitter

    IPC8bits.U2IP = 2;
    IEC1bits.U2RXIE = 1;
    IFS1bits.U2RXIE = 0;

    U2MODEbits.ON = 1; // Enable UART2

    EnableInterrupts(); // Global interrupt enable

    count = 15;

    while(1) {}
    return 0;
}


void _int_(32) isr_uart2(void) {
    if(IFS1bits.U2RXIF == 1) {
        char byte = U2RXREG; // Read received character
        if(byte == 'U') {
            count ++;
            if (count == 16) {
                count = 0;
            }
        }
        if(byte == 'R') {
            count = 0;
            puts("RESET\n");
        }
        LATE = (LATE & 0xFFE1) | (count << 1); // Update output
        IFS1bits.U2RXIF = 0; // Reset interrupt flag
    }
}

void puts(char *str)
{
    while (*str != '\0')
    {
        putc(*str);
        str++;
    }
}

void putc(char byte)
{
    // wait while UART2 UTXBF == 1
    while (U2STAbits.UTXBF == 1);
    // Copy "byte" to the U2TXREG register
    U2TXREG = byte;
}
