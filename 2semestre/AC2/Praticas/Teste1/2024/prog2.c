#include <detpic32.h>

void delay(int ms) {
    resetCoreTimer();
    while(readCoreTimer() < ms);
}

void display(unsigned int value) {
    static const int segments[] = {0x3F, 0x06, 0x5b, 0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F, 0x67, 0x5F, 0x7C, 0x39, 0x5E, 0x79, 0x71};

    int number = value % 10;

    LATDbits.RD5 = 0;
    LATB = (LATB & 0x80FF) | (segments[value] << 8); 
}

int main(void) {
    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4= 0; 
    AD1CON1bits.SSRC = 7; 
    AD1CON1bits.CLRASAM = 1;
    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 2-1;
    AD1CHSbits.CH0SA = 4;
    AD1CON1bits.ON = 1;

    TRISB = (TRISB & 0x80FF);
    TRISD = (TRISD & 0xFFDF); 
    
    TRISEbits.RE1 = 0;
    LATEbits.RE1 = 0;

    int media;
    int volt;

    while(1) {
        AD1CON1bits.ASAM = 1;
        
        while( IFS1bits.AD1IF == 0 );

        media = (ADC1BUF0 + ADC1BUF1) / 2;
        printInt(media, 16 | 3 << 16);
        putChar('\n');

        volt = 1023/10;
        display(volt);

        LATEbits.RE1 = !LATEbits.RE1;

        delay(3333333);

        IFS1bits.AD1IF = 0;
    }

    return 0;
}