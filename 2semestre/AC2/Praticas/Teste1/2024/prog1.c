#include <detpic32.h>

void delay(int ms) {
    resetCoreTimer();
    while(readCoreTimer() < ms);
}

int main(void) {
    TRISE = (TRISE & 0xFFC3);
    TRISBbits.RB2 = 1;

    int cnt = 0;
    int freq;

    while(1) {
        LATE = (LATE & 0xFFC3) | (cnt << 2);

        printInt(cnt, 10 | 2 << 16);
        putChar('\n');
        
        if(cnt == 0) {
            cnt = 11;
        } else {
            cnt = cnt - 1;
        }

        if(PORTBbits.RB2 == 1) {
            freq = 3636364;
        } else {
            freq = 8695652;
        }

        delay(freq)
    }

    return 0;
}