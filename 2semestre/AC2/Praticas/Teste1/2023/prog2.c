#include <detpic32.h>

void delay(int ms) {
    resetCoreTimer();
    while(readCoreTimer() < ms)
}

void display(unsigned int value) {
    static const int segments[] = {0x3F, 0x06, 0x5b, 0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F, 0x67, 0x5F, 0x7C, 0x39, 0x5E, 0x79, 0x71};

    int number = value % 16; 
    int flags;

    if(PORTBbits.RB1 == 1) {
        flags = 0;
    } else if(PORTBbits.RB1 == 0) {
        flags = 1;
    }

    if(flags == 1) {
        LATDbits.RD5 = 1;
        LATDbits.RD5 = 0;
        LATB = (LATB & 0x80FF) | (segments[number] << 8);
    } else {
        LATDbits.RD5 = 0;
        LATDbits.RD5 = 1;
        LATB = (LATB & 0x80FF) | (segments[number] << 8);
    }
}

int main(void) {
    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4= 0; 
    AD1CON1bits.SSRC = 7; 
    AD1CON1bits.CLRASAM = 1;
    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 4-1;
    AD1CHSbits.CH0SA = 4;
    AD1CON1bits.ON = 1;

    TRISB = (TRISB & 0x80FF);
    TRISD = (TRISD & 0xFF9F);
    
    TRISBbits.RB1 = 1;
    TRISEbits.RE4 = 0;
    LATEbits.RE4 = 0;

    int media;
    int volt;

    while(1) {
        AD1CON1bits.ASAM = 1;
        
        while( IFS1bits.AD1IF == 0 ); 

        media = (ACD1BUF0 + ADC1BUF1 + ADC1BUF2 + ADC1BUF3) / 4;
        printStr("i)");
        printInt(media, 2 | 10 << 16);

        volt = (1023 / 9) + 3;
        display(volt);
        
        delay(1666667);

        LATEbits.RE4 = !LATEbits.RE4;

        IFS1bits.AD1IF = 0;
    }

    return 0;
}