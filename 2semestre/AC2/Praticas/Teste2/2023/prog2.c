#include <detpic32.h>

volatile int tmp = 0;

int main(void) {
    TRISB = (TRISB & 0x80FF);
    TRISD = (TRISD & 0xFF9F);

    // Configure ADC
    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4 = 0;
    AD1CON1bits.SSRC = 7;
    AD1CON1bits.CLRASAM = 1;
    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 1; // 2 samples per interrupt 2-1
    AD1CHSbits.CH0SA = 4;
    AD1CONbits.ON = 1;    

    // Configure T3 (1, 2, 4, 8, 16, 32, 64, 256)
    // 140Hz
    // k_prescaler = 20MHz / ((65535 + 1) * fout(140Hz)) = 2,18 -> 4
    // prescaler 1:4 -> 2
    // fout = 20MHz / (4 * (PR3 + 1)) = 140Hz
    // PR3 = 20MHz /(140 * 4) - 1 = 35714

    T3CONbits.TCKPS = 2;     // 1:4 prescaler
    PR3 = 35714;             // Fout = 20MHz / (4 * (35714 + 1)) = 140Hz
    TMR3 = 0;                // Clear timer T3 count register
    T3CONbits.TON = 1;       // Enable timer T3

    IPC3bits.T3IP = 2;       // Set priority for timer T3 interrupt
    IEC0bits.T3IE = 1;       // Enable timer T3 interrupt
    IFS0bits.T3IF = 0;       // Reset timer T3 interrupt flag

    EnableInterrupts();      // Global interrupt enable

    while(1) {
        AD1CON1bits.ASAM = 1; // Start conversion
        while( IFS1bits.AD1IF == 0 );

        int i, media = 0;
        int p* = (int *) &ADC1BUF0;
        for(i = 0; i < 2; i++) {
            media += p[i * 4];
        }
        media = media / 2;
        tmp = ((media * 65 + 511) / 1023) + 10;

        IFS1bits.AD1IF = 0;
        delay(200);
    }
    return 0;
}

void _int_(12)isr_T3(void) {
    send2displays(tmp);
    IFS0bits.T3IF = 0;
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