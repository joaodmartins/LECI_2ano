#include <detpic32.h>

volatile int temp = 0;

int main(void)
{
    TRISB = (TRISB & 0x80FF); // RB8-RB14 as outputs
    TRID = (TRISD & 0xFF9F);  // RD5-RD6 as outputs

    TRISBbits.TRISB4 = 1;     // RB4 as input (analog)
    AD1PCFGbits.PCFG4 = 0;    // RB4 configured as analog input
    AD1CON1bits.SSRC = 7;     // Internal counter ends sampling and starts conversion
    AD1CON1bits.CLRASAM = 1;  // Stop conversions when the 1st A/D converter interrupt is generated
    AD1CON3bits.SAMC = 16;    // Sample time is 16 TAD (TAD = 100 ns)
    AD1CON2bits.SMPI = 2 - 1; // Interrupt is generated after 2 samples
    AD1CHSbits.CH0SA = 4;     // Select channel 4 as input
    AD1CON1bits.ON = 1;       // Enable A/D converter

    // Configure timer 2 (1, 2, 4, 8, 16, 32, 64, 256)
    // 120Hz
    // k_prescaler = 20MHz / ((65535 + 1) * fout(120)) = 2,54 -> 4
    // prescaler 1:4 -> 2
    // fout = 20MHz / (4 * (PR2 + 1)) = 120Hz
    // PR2 = 20MHz / (4 * 120) - 1 = 41665

    T2CONbits.TCKPS = 2;     // 1:4 prescaler
    PR2 = 41665;             // Fout = 20MHz / (4 * (41665 + 1)) = 120Hz
    TMR2 = 0;                // Clear timer T2 count register
    T2CONbits.TON = 1;       // Enable timer T2

    IPC2bits.T2IP = 2;       // Set priority for timer T2 interrupt
    IEC0bits.T2IE = 1;       // Enable timer T2 interrupt
    IFS0bits.T2IF = 0;       // Reset timer T2 interrupt flag

    EnableInterrupts();      // Global interrupt enable

    while (1) {
        AD1CON1bits.ASAM = 1; // Start conversion
        while (IFS1bits.AD1IF == 0); // Wait while conversion not done (AD1IF == 0)

        int i, media = 0;
        int *p = (int *)(&ADC1BUF0);
        for (i= 0; i < 2; i++) {
            media += p[i * 4];
        }
        media = media / 2;
        temp = ((media * 50 + 511) / 1023) + 15;

        IFS1bits.AD1IF = 0; // Reset AD1IF flag
        delay(100);
    }
    return 0;
}

void _int_(8) isr_T2(void) {
    send2displays(temp); // Send temperature to displays
    IFS0bits.T2IF = 0; // Reset T2IF flag
}

char tobcd(char val) {
    return (val / 10 << 4) | val % 10;
}

void send2displays(char val) {
    static const char segments[] = {
        0x3F, 0x06, 0x5B, 0x4F,
        0x66, 0x6D, 0x7D, 0x07,
        0x7F, 0x6F};

    static int flag = 0;
    char high = tobcd(val) << 4;
    char low = tobcd(val) & 0x0F;

    if (flag)
    {
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;
        LATB = (LATB & 0x80FF) | (segments[high] << 8);
        flag = 0;
    }
    else
    {
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;
        LATB = (LATB & 0x80FF) | (segments[low] << 8);
        flag = 1;
    }
}

void delay(int ms) {
    resetCoreTimer();
    while(readCoreTimer() < ms * 20000);
}