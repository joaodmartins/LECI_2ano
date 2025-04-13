#include <detpic32.h>

void delay(int ms) {
    resetCoreTimer();
    while(readCoreTimer() < ms);
}

int main(void) {
    // SET RE5 ... RE2 AS OUTPUTS
    TRISE = TRISE & 0xFFC3; // XXXX XXXX XX00 00XX

    // SET RB2 AS INPUT
    TRISBbits.RB2 = 1; // RB2 = 1 (input)

    int cnt = 0; // Initialize counter
    int freq;

    while(1) {
        LATE = (LATE & 0xFFC3) | (cnt << 2); // Set RE5...RE2 to cnt value

        printInt(cnt, 10 | 2 << 16);
        putChar('\n');

        if (cnt == 0) {
            cnt = 11;
        } else {
            cnt--;
        }

        if(PORTBbits.RB2 == 0) {
            freq = 8695652; // DS3 OFF, f = 2.3Hz
        } else {
            freq = 3636364; // DS3 ON, f = 1.5Hz
        }

        delay(freq);
    }

    return 0;
}