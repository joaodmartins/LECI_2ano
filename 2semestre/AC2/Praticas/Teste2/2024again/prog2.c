#include <detpic32.h>

volatile char temp = 0;

void delay(int ms) {
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}

char tobcd(char val) {
    return (((val / 10) << 4) | (val %10));
}

char send2Display(char val) {
    static const char disp7Scodes[16] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    static char flag = 0;

    int high_digit = value << 4;
    int low_digit = value & 0x0F;

    if(flag) {
        LATD = (LATD & 0xFF9F) | 0x0040;
        LATE = (LATE & 0x80FF) | (disp7Scodes[high_digit] << 8);
    } else {
        LATD = (LATD & 0xFF9F) | 0x0020;
        LATE = (LATE & 0x80FF) | (disp7Scodes[low_digit] << 8);
    }
    flag = !flag;
}

int main(void) {
    TRISB = (TRISB & 0x80FF);
    TRISD = (TRISD & 0xFF9F);
    
    // Configure AD
    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4 = 0;
    AD1CON1bits.SSRC = 7;
    AD1CON1bits.CLRASAM = 1;
    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 1;
    AD1CHSbits.CH0SA = 4;
    AD1CON1bits.ON = 1;

    // Configre T3
    // 250Hz
    // k_prescaler = 20MHz /((65535 + 1) fout(250)) = 1,22 -> 2
    // prescaler 1:2 -> 1
    // fout = 20MHz / (2 * (PR3 + 1)) = 250Hz
    // PR3 = 20MHz / (2 * 250Hz) - 1 = 39999

    T3CONbits.TCKPS = 1;
    PR3 = 39999;
    TMR3 = 0;
    T3CONbits.TON = 1;

    IPC3bits.T3IP = 2;
    IEC0bits.T3IE = 1;
    IFS0bits.T2IF = 0;

    EnableInterrupts();


    while(1) {
        AD1CON1bits.ASAM = 1;
        while( IFS1bits.AD1IF == 0 );

        int i, media = 0;
        int p* = (int *) &ADC1BUF0;
        for(i = 0; i < 2; i++) {
            media += p[i * 4];
        } 
        media = media / 2
        temp = ((media * 65 + 511) / 1023) + 7;
        IFS1bits.AD1IF = 0;
        delay(200);
    }
    return 0;
}

void _int_(12) isr_T3(void) {
    send2Display(tobcd(temp)),
    IFS0bits.T3IF = 0;
}