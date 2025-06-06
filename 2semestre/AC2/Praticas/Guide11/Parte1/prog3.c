#include <detpic32.h>

void puts(char *str);
void putc(char byte);

int main(void)
{
    TRISCbits.TRISC14 = 0;
    LATCbits.LATC14 = 0;

    // Configure UART2: 115200, N, 8, 1
    // 1 - Configure BaudRate Generator
    U2BRG = 10; // BaudRate = 115200 -> (20000000 / (16 * 115200)) - 1 = 10
    U2MODEbits.BRGH = 0;
    // 2 - Configure number of data bits, parity and number of stop bits
    U2MODEbits.PDSEL = 0; // 00 = 8-bit data, no parity
    U2MODEbits.STSEL = 0; // 0 = 1 Stop bit
    // 3 - Enable the transmitter and receiver modules
    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;
    // 4 - Enable UART2
    U2MODEbits.ON = 1;

    // Configure UART2 interrupts, with RX interrupts enabled and TX interrupts disabled:
    // enable U2RXIE disable U2TXIE (register IEC1)
    IEC1bits.U2RXIE = 1;
    IEC1bits.U2TXIE = 0;
    // Set UART2 priority level (register IEC1)
    IPC8bits.U2IP = 1;
    // clear Interrupt Flag bit U2RXIF (register IFS1)
    IFS1bits.U2RXIF = 0;
    // define RX interrupt mode (URXISEL bits)
    U2STAbits.URXISEL = 0; // has 1 character

    // Enable Global Interrupts
    EnableInterrupts();

    while (1)
    {
        IdleMode();
    }
    return 0;
}

void _int_(32) isr_uart2(void)
{
    if (IFS1bits.U2RXIF == 1)
    {
        // Read character from FIFO (U2RXREG)
        char a = U2RXREG;
        // Send the character using putc()
        if (a == '?')
        {
            puts("AC2-Guiao 11");
        }
        else if (a == 'T')
        {
            LATCbits.LATC14 = 1;
            putc(a);
        }
        else if (a == 't')
        {
            LATCbits.LATC14 = 0;
            putc(a);
        }
        else
        {
            putc(a);
        }
    }
    // Clear UART2 Rx interrupt flag
    IFS1bits.U2RXIF = 0;
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
    while (U2STAbits.UTXBF == 1)
        ;
    // Copy "byte" to the U2TXREG register
    U2TXREG = byte;
}
