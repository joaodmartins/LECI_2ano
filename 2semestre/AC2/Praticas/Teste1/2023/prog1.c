#include <detpic32.h>

void delay(int ms) {
    resetCoreTimer();
    while(readCoreTimer() < ms);
}

int main(void) {
    TRISE = (TRISE & 0xFF03); // RE7-RE2 saidas
    TRISB = (TRISB & 0x0005); // RB2 e RB0 entradas

    int freq = 2739726; // 7.3Hz
    int cnt = 48;

    while(1) {
        LATE = (LATE & 0xFF03) | (cnt << 2);

        if((PORTBbits.RB2 == 1) && (PORTBbits.RB0 == 1)) {
            freq = 2739726; // 7.3Hz
        } else if((PORTBbits.RB2 == 0) && (PORTBbits.RB0 == 0)) {
            freq = 4347826; // 4.6Hz
        }

        if(cnt = 3) {
            cnt = 48;
        } else {
            cnt = (cnt >> 1);
        }
    }
}