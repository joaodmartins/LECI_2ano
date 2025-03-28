#include <detpic32.h>

int main(void) {
    static const char disp7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    int dips, code;

    LATB = (LATB & 0x80FF);           // 1000 0000 1111 1111
    LATD = (LATD & 0xFF9F);           // 1111 1111 1001 1111

    TRISB = (TRISB | 0x000F);       // in 
    TRISB = (TRISB & 0x80FF);       // out
    TRISD = (TRISD & 0xFF9F);       // out

    LATD = (LATD | 0x0040);         // 0000 0000 0100 0000

    while(1) {
        dips = PORTB & 0x000F;
        code = disp7scodes[dips];
        LATB = (LATB & 0x80FF) | (code << 8);
    }
    return 0;
}