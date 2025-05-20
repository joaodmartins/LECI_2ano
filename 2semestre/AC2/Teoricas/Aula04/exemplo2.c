#include <detpic32.h>

void delay(int ms);

int main(void) {
    // reset
    LATD = (LATD & 0xFFFE);

    // configure ports
    TRISD = (TRISD & 0xFFFE); // Bit 0 out

    while(1) {
        LATD = (LATD | 0x0001);
        delay(100);
        LATD = (LATD & 0xFFFE);
        delay(900);
    }
    return 0;
}

void delay(int ms) {
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}