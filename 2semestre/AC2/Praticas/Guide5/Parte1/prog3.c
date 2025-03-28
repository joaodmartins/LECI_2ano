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
    static char displayFlag = 0; // static variable: doesn't loose its
                                // value between calls to function
    int digit_low = value & 0x0F;
    int digit_high = value >> 4;
    // if "displayFlag" is 0 then send "digit_low" to display_low
    if(displayFlag == 0) {
        LATD = (LATD & 0xFF9F);
        LATD = (LATD | 0x0020);
        LATB = (LATB & 0x80FF) | (disp7Scodes[digit_low] << 8);
    }
    // else send "digit_high" to didplay_high
    else {
        LATD = (LATD & 0xFF9F);
        LATD = (LATD | 0x0040);
        LATB = (LATB & 0x80FF) | (disp7Scodes[digit_high] << 8);
    }
    // toggle "displayFlag" variable
    displayFlag = !displayFlag;
}

void delay(int ms) {
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}
