#include <detpic32.h>

int main(void) {
    // reset
    LATB = (LATB & 0xFFFD);   // 1111 1111 1111 1101
    LATE = (LATE & 0xFFFD);

    TRISB = (TRISB | 0x0002); // in
    TRISE = (TRISE & 0xFFFD); // out

    while(1) {
        if(PORTBbits.RB2 = 1) {
            LATEbits.LATE2 = 1;
        } else {
            LATEbits.LATE2 = 0;
        }
    }

    return 0;
}