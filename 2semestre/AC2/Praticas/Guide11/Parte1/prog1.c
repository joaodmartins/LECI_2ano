#include <detpic32.h>

int main(void) {
    // Configure UART2: 115200, N, 8, 1
    // 1 - Configure BaudRate Generator
    U2BRG = 10;     // BaudRate = 115200 -> (20000000 / (16 * 115200)) - 1 = 10

    // Configure UART2 interrupts, with RX interrupts enabled and TX interrupts disabled:
    // enable U2RXIE disable U2TXIE (register IEC1)

    // Set UART2 priority level (register IEC1)

    // clear Interrupt Flag bit U2RXIF (register IFS1)

    // define RX interrupt mode (URXISEL bits)

    // Enable Global Interrupts

    while(1) {
        IdleMode();
    }
    return 0;
}