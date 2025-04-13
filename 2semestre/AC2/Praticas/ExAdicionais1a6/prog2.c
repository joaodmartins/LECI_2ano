#include <detpic32.h>

void delay(int ms) {
    resetCoreTimer();
    while(readCoreTimer() < ms);
}

int main(void) {

    while(1) {
        int key = inKey();
        if(key == 0x30) {
            LATEbits.RE0 = 1;
            LATEbits.RE1 = 0;
            LATEbits.RE2 = 0;
            LATEbits.RE3 = 0;
        } else if(key == 0x31) {
            LATEbits.RE0 = 0;
            LATEbits.RE1 = 1;
            LATEbits.RE2 = 0;
            LATEbits.RE3 = 0;
        } else if(key == 0x32) {
            LATEbits.RE0 = 0;
            LATEbits.RE1 = 0;
            LATEbits.RE2 = 1;
            LATEbits.RE3 = 0;
        } else if(key == 0x33) {
            LATEbits.RE0 = 0;
            LATEbits.RE1 = 0;
            LATEbits.RE2 = 0;
            LATEbits.RE3 = 1;
        } else {
            LATE = (LATE | 0x000F);
            delay(20000000);
            LATE = (LATE & 0xFFF0);
        }
    }

    return 0;
}