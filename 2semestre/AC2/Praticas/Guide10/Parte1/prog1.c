#include <detpic32.h>

int main(void) {
    // Configure UART2:
    // 1 - COnfigure BaudRate Generator
    U2BRG = 10;     // BaudRRate = 115200 -> (20000000) / (16 * 115200)) - 1 = 10 
    U2MODEbits.BRGH = 0;
    // 2 - Configure number of data bits, parity and number of stop bits (see U2MODE register)
    U2MODEbits.PDSEL = 0;       // 00 = 8.bit data, no parity
    U2MODEbits.STSEL = 0;       // 0 - 1 Stop bit
    // 3 . Enable transimitter and receiver modules (see register U2STA)
    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;
    // 4 - Enable UART2 (see register U2MODE)
    U2MODEbits.ON = 1;
}