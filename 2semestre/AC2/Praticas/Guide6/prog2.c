#include <detpic32.h>

int main(void) {
    volatile int aux;

    TRISBbits.TRISB4 = 1;       // RB4 digital output disconnected
    AD1PCFGbits.PCFG4= 0;       // RB4 configured as analog input

    AD1CON1bits.SSRC = 7;       // Conversion trigger selection bits: in this mode an internal counter ends sampling and starts conversion
    AD1CON1bits.CLRASAM = 1;    // Stop conversions when the 1st A/D converter interrupt is generated. At the same time,    
                                // hardware clears the ASAM bit
    AD1CON3bits.SAMC = 16;      // Sample time is 16 TAD (TAD = 100 ns)
    AD1CON2bits.SMPI = 1-1;     // Interrupt is generated after 0 samples

    AD1CHSbits.CH0SA = 4;       // input analog channel 4
    AD1CON1bits.ON = 1;         // Enable A/D converter

    TRISDbits.TRISD11 = 0;

    // Configure the A/D module and port RB4 as analog input
    while(1) {
        AD1CON1bits.ASAM = 1;   // start conversion
        LATDbits.LATD11 = 1;     // Set LATD11
        while(IFS1bits.AD1IF == 0);     // Wait while conversion not done
        LATDbits.LATD11 = 0;    // Reser LATD11
        aux = ADC1BUF0;         // Read conversion result (ADC1BUF0) to "aux" variable
        IFS1bits.AD1IF = 0;     // Reset AD1IF (should be done after reading the conversion result)
    }
    return 0;
}