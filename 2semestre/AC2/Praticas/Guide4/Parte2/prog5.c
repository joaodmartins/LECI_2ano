#include <detpic32.h>

void delay(int ms);

int main(void) {
    unsigned char segment;

    LATB = (LATB & 0x80FF);           // 1000 0000 1111 1111
    LATD = (LATD & 0xFF9F);           // 1111 1111 1001 1111

    TRISB = (TRISB & 0x80FF);
    TRISD = (TRISD & 0xFF9F); 

    while(1) {
        segment = 1;
        for(int i = 0; i < 7; i++) {

            LATB = (LATB & 0x80FF) | (segment << 8);

            delay(100);        // 10Hz = 1000 / 10 = 100ms
            // delay(20)    50Hz = 1000 / 50 = 20ms
            // delay(10)    100Hz = 1000 / 100 = 10ms
            segment = segment << 1;
        }

        LATB = LATB ^ 0x7F00;        // 0111 1111 0000 0000
        LATD = LATD ^ 0x0060;        // 0000 0000 0110 0000
    }
    return 0;
}

void delay(int ms) {
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}