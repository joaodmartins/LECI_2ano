#include <detpic32.h>

void delay(int ms) {
    resetCoreTimer();
    while(readCoreTimer() < ms * 20000);
}

void setDutyCycle(char dutyCycle) {
    OC4RS = ((PR3 + 1) * dutyCycle) / 100;
}

int main(void) {
    TRISBbits.RB1 = 1; // DS2 as input 

    // Configure T3 (1, 2, 4, 8, 16, 32, 64, 256)
    // 130Hz
    // k_prescaler = 20MHz / ((65535 + 1) * fout(130Hz)) = 2,35 -> 4
    // prescaler 1:4 -> 2
    // fout = 20MHz / (4 * (PR3 + 1)) = 130Hz
    // PR3 = 20MHz / (4 * 130Hz) -1 = 38461

    T2CONbits.TCKPS = 2;    // 1:4 prescaler
    PR3 = 38461;            // Fout = 130Hz
    TMR3 = 0;               // Reset timer T3
    T3CONbits.TON = 1;      // Enable timer T3

    OC4CONbits.OCM = 6;     // PWM mode on OCx; fault pin disabled
    OC4CONbis.OCTSEL = 0;   // Use Timer T3 as time base
    setDutyCycle(50);
    OC4CONbits.ON = 1;      // Enable OC1 module

    static int flag = 0;

    while(1) {
        if(PORTBbits.RB1 == 0) {
            if(flag) {
                setDuttyCycle(25);
            } else {
                setDutyCycle(75);
            }
        } else if (PORTBbits.RB1 == 1) {

        }
        delay(1300);
    }
    return 0;
}
