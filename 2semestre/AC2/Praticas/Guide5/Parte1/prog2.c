#include <detpic32.h>

void send2displays(unsigned char value);
void delay(int ms);

int main(void)
{
    // configure RB8-RB14 as outputs
    LATB = (LATB & 0x80FF);     // 1000 0000 1111 11111
    TRISB = (TRISB & 0x80FF);
    // configure RD5-RD6 as outputs
    LATD = (LATD & 0xFF9F);         // 1111 1111 1001 1111
    TRISD = (TRISD & 0xFF9F);
    while(1) {
        send2displays(0x15);
        delay(500);
    }
}

void send2displays(unsigned char value) {
    static const char disp7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    int dh, dl;
    // select display high
    LATD = (LATD | 0xFF9F);
    LATD = (LATD | 0x0040);
    // send digit_high (dh) to display:
    dh = (value >> 4);
    LATB = (LATB & 0x80FF) | (disp7Scodes[dh] << 8);
    // select display low
    LATD = (LATD | 0xFF9F);
    LATD = (LATD | 0x0020);
    // send digit_low (dl) to display:
    dl = (value & 0x0F);
    LATB = (LATB & 0x80FF) | (disp7Scodes[dl] << 8);
}

void delay(int ms) {
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}
