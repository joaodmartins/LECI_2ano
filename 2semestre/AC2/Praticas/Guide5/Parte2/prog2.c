#include <detpic32.h>

void send2displays(unsigned char value);
void delay(int ms);
unsigned char toBcd(unsigned char value);

int main(void) {
    // declare variables
    int i, counter;
    // initialize ports
    LATB = (LATB & 0x80FF);
    LATD = (LATD & 0xFF9F);
    LATE = (LATE & 0xFF00);

    TRISB = (TRISB | 0x000F);
    TRISB = (TRISB & 0x80FF);
    TRISD = (TRISD & 0xFF9F);
    TRISE = (TRISE & 0xFF00);

    counter = 0;
    while(1) {
        i = 0;
        do {
            send2displays(toBcd(counter));
            LATE = (LATE & 0xFF00) | toBcd(counter);
            // wait 20 ms (1/50Hz)
            delay(10);
        } while(++i < refresh);
        // increment counter (mod 256)
        if((PORTB & 0x0001) == 0x0001) {
            if(++counter > 59) {
                counter = 0;
            }
        } else {
            if(--counter < 0) {
                counter = 59;
            }
        }
    }
    return 0;
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

unsigned char toBcd(unsigned char value) {
    return ((value / 10) << 4) + (value % 10);
}

void delay(int ms) {
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}
