#include <detpic32.h>

void delay(int microsegundos)
{
    resetCoreTimer();
    while (readCoreTimer() < microsegundos * 20)
}

void setDutyCycle(unsigned int dutyCycle)
{
    // Set the duty cycle for OC2
    OC2RS = ((41666 + 1) * dutyCycle) / 100; // PR3 = 41666 for 120Hz
}

int main(void)
{
    TRISB = (TRISB | 0x0005); // DS3 and DS1 as inputs
    TRISD = (TRISD & 0xFFFD); // OC2 as output

    // Configure Timer 3 (1, 2, 4, 8, 16, 32, 64, 256)
    // 120Hz
    // k_prescaler = 20MHz / ((65535 + 1) * fout(120)) = 2,54 -> 4
    // Prescaler 1: 4 -> 2
    // fout = 20MHz / (4 * (PR3 + 1)) = 120Hz
    // PR3 = 20MHz / (120 * 4) - 1 = 41666

    T3CONbits.TCKPS = 2; // 1:4 prescaler
    PR3 = 41666;         // Fout = 20MHz / (4 * (41666 + 1)) = 120Hz
    TMR3 = 0;            // Clear timer T3 count register
    T3CONbits.TON = 1;   // Enable timer T3

    OC2CONbits.OCM = 6;    // PWM mode on OC2, fault pin disabled
    OC2CONbits.OCTSEL = 1; // Use timer T3 as the time base for OC2
    setDutyCycle(75);
    OC2CONbits.ON = 1; // Enable OC2

    while (1)
    {
        if (PORTBbits.RB2 == 0 &&PORTBbits.RB = = 0)
        {
            setDutyCycle(30);
        }
        else if (PORTBbits.RB2 == 1 && PORTBbits.RB0 == 1)
        {
            setDutyCycle(55);
        }
        delay(360);
        IFS0bits.T3IF = 0;
    }
    return 0;
}