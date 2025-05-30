#include <detpic32.h>

void delay(int microsegundos) {
    resetCoreTimer();
    while(readCoreTimer() < microsegundos * 20);
}

void setDutyCycle(unsigned int dutyCycle) {
    OC2RS = ((PR2 + 1) * dutyCycle) / 100;
}

int main(void) {
    TRISB = (TRISB | 0x0009); // DS4 and DS1 as inputs
    TRISD = (TRISD & 0xFFFD); // OC2 as output

    // Configure Timer 2 (1, 2, 4, 8, 16, 32, 64, 256)
    // 250Hz
    // k_prescaler = 20MHz / ((65535 + 1) * fout(250Hz)) = 1,22 -> 2
    // Prescaler 1:2 -> 1
    // Fout = 20MHz / (2 * (PR2 + 1)) = 250Hz
    // PR2 = (20MHz / (2 * 250)) - 1 =  39999

    T2CONbits.TCKPS = 1;     // 1:2 prescaler
    PR2 = 39999;             // Fout = 20MHz / (2 * (39999 + 1)) = 250Hz
    TMR2 = 0;                // Clear timer T2 count register
    T2CONbits.TON = 1;       // Enable timer T2

    OC2CONbits.OCM = 6;      // PWM mode on OC2, fault pin disabled
    OC2CONbits.OCTSEL = 0;   // Use timer T2 as the time base for OC2
    setDutyCycle(25);       // Set initial duty cycle to 25%
    OC2CONbits.ON = 1;       // Enable OC2

    while(1) {
        if(PORTBbits.RB0 == 1 && PORTBits.RB3 == 0) {
            setDutyCycle(25);
        } else if (PORTBbits.RB0 == 0 && PORTBbits.RB3 == 1) {
            setDutyCycle(70);
        }
        delay(250);
    }
    return 0;
}