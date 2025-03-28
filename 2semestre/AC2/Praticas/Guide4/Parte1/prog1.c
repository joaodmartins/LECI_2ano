#include <detpic32.h>

void delay(int ms);

int main(void) {
    LATC = LATC & 0xBFFF;     // 1011 1111 1111 1111
    TRISC = TRISC & 0xBFFF;    

    while(1) {
        delay(500);
        LATC = LATC ^ 0x4000; // 0100 0000 0000 0000
    }
    return 0;
}

void delay(int ms) {
    resetCoreTimer();
    while(readCoreTimer() < (20000 * ms));
}

