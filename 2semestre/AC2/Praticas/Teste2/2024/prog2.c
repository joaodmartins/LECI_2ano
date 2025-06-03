#include <detpic32.h>

volatile unsigned int temp = 0;

void delay(int ms) {
    resetCOreTimer();
    while(readCoreTImer() < ms * 20000);
}

unsigned char tobcd (unsigned char value) {
    return (value / 10) << 4 |  value % 10;
}

void send2Display(unsigned char value) {
    static const char disp7Scodes[16] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    static char displayFlag = 0;

    int high_digit = value << 4;
    int low_digit = value & 0x0F;

    if(displayFlag) {
        LATD = (LATD & 0xFF9F) | 0x0040;
        LATB = (LATEB & 0x80FF) | (high_digit << 8);
    } else {
        LATD = (LATD & 0xFF9F) | 0x0020;
        LATB = (LATEB & 0x80FF) | (low_digit << 8);
    }
    displayFlag = !displayFlag;
}

int main(void) {
    TRISB = (TRISB & 0x80FF);
    TRISD = (TRISD & 0xFF9F);

    // Configure ADC
    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4 = 0;
    AD1CON1bits.SSRC = 7;
    AD1CON1bits.CLRASAM = 1
    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 1;
    AD1CHSbits.CH0SA = 4;
    AD1CON1bits.ON = 1;

    // Configure T3 (1, 2, 4, 8, 16, 32, 64, 256)
    // 250Hz
    // k_prescaler = 20MHz / ((65535 + 1) * fout(250)) = 1,22 -> 2
    // prescaler 1:2 -> 1
    // fout = 20MHz / (2 * (PR3 + 1)) = 250Hz
    // PR3 = 20MHz / (2 * 250) - 1 = 39999

    T2CONbits.TCKPS = 1;    // 1:2 prescaler
    PR3 = 39999;
    TMR3 = 0;               // Reset timer T3
    T3CONbits.TON = 1;      // Enable timer T3

    IPC3bits.T3IP = 2; 
    IEC0bits.T3IE = 1;
    IFS0bits.T3IF = 0;

    while(1) {
        AD1CON1bits.ASAM = 1;
        while(IFS1bits.AD1IF == 0);

        int i, media = 0;
        int p* = (int * ) & ADC1BUF0;
        for(i = 0; i < 2; i++) {
            media += p[i * 4]; 
        }
        media = media / 2;
        temp = ((media * 66 + 511) / 1023) + 7;
        IFS1bits.AD1IF = 0;
        delay(200);
    }
    return 0;
}

void _int_(12) isr_T3(void) {
    send2Display(tobcd(temp));
    IFS0bits.T3IF = 0;
}