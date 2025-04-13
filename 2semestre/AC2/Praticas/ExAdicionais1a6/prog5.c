#include <detpic32.h>

void delay(int ms) {
    resetCoreTimer();
    while(readCoreTimer() < ms);
}

void send2displays(unsigned int value) {
    static const char d7Sc[] = {
        0x3F, 0x06, 0x5B, 0x4F,
        0x66, 0x6D, 0x7D, 0x07,
        0x7F, 0x6F, 0x77, 0x7C,
        0x39, 0x5E, 0x79, 0x71
    };

    static int displayFlag = 0;
    int digit_low = value & 0x0F;
    int digit_high = value >> 4;

    if(displayFlag) {
        LATD = (LATD & 0xFF9F) | 0x0040;
        LATB = (LATB & 0x80FF) | (d7Sc[digit_high] << 8);
    } else {
        LATD = (LATD & 0xFF9F) | 0x0020;
        LATB = (LATB & 0x80FF) | (d7Sc[digit_low] << 8);
    }

    displayFlag = !displayFlag;
}

int main(void) {

    int cnt = 0;
    unsigned int freq = 2000000;
    int hz = 10;

    while(1) {
        putChar('\r');
        printInt(cnt, 10 | 2 << 16);

        if(cnt == 99) {
            cnt = 0;
        } else {
            cnt++;
        }
        char key = inKey();
        if (key == 0x30){
            freq = 10000000;
            hz = 2;
        }
        if (key == 0x31) {
            freq = 5000000;
            hz = 4;
        }
        if (key == 0x32) {
            freq = 2500000;
            hz = 8;
        }
        if (key == 0x33) {
            freq = 2000000;
            hz = 10;
        } 
        if (key == 0x28) {
            putChar('\r');
            printInt(cnt, 10 | 2 << 16);
            putChar(', ');
            printInt10(hz, 10);
            printString(" Hz")
        } 
        delay(freq);
    }

    return 0;
}