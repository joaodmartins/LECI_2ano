#include <detpic32.h>

void delay(int ms) {
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}

void setDutyCycle(unsigned int dutyCycle)
{
    OC4RS = ((PR2 + 1) * dutyCycle) / 100;
}

int main(void)
{
    TRISB = (TRISB & 0xFFFD);

    // Configure T3 (1, 2, 4, 8, 16, 32, 64, 256)
    // 130Hz
    // k_prescaler = 20MHz / ((65535 + 1) * fout(130)) = 2,35 -> 4
    // prescaler 1:4 -> 2
    // fout = 20MHz / (4 * (PR3 + 1)) = 130Hz
    // PR3 = 20MHZ / (4 * 130) - 1 = 38 461

    T3CONbits.TCKPS = 2;
    PR3 = 38461;
    TMR3 = 0;
    T3CONbits.TON = 1;

    OC4CONbits.OCM = 6;
    OC4CONbits.OCTSEL = 0;
    setDutyCycle(50);
    OC4CONbits.ON = 1;

    static int flag = 0;

    while (1)
    {
        if (PORTBbits.RB1 == 0)
        {
            if (flag)
            {
                setDutyCycle(75);
            }
            else
            {
                setDutyCycle(25);
            }
            flag = !flag;
        }
        delay(1300);
    }
    return 0;
}