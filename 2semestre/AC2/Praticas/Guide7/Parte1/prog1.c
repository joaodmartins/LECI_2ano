#include <detpic32.h>

int main(void) {
    TRISBbits.TRISB4 = 1;       // RB4 digital output disconnected
    AD1PCFGbits.PCFG4= 0;       // RB4 configured as analog input
    AD1CON1bits.SSRC = 7;       // Conversion trigger selection bits: in this mode an internal counter ends sampling and starts conversion
    AD1CON1bits.CLRASAM = 1;    // Stop conversions when the 1st A/D converter interrupt is generated. At the same time,    
                                // hardware clears the ASAM bit
    AD1CON3bits.SAMC = 16;      // Sample time is 16 TAD (TAD = 100 ns)
    AD1CON2bits.SMPI = 1-1;     // Interrupt is generated after 0 samples
    AD1CHSbits.CH0SA = 4;       // input analog channel 4
    AD1CON1bits.ON = 1;         // Enable A/D converter

    // Configure interrupt system
    IPC6bits.AD1IP = 2;         // configure priority of A/D interrupts
    IFS1bits.AD1IF = 0;         // clear A/D interrupt flag
    IEC1bits.AD1IE = 1;         // enable A/D interrupts

    EnableInterrupts();         // Global interrupt Enable
    
    // Start A/D conversation
    AD1CON1bits.ASAM = 1;

    while(1);                   // all activity is done by the ISR

    return 0;
}


void _int_(27) isr_adc(void)    // Replace VECTOR by the A/D vector
                                // number - see "PIC32 family data
                                // sheet" (pages 74-76)
                                // ADC = 27
{
    // Read conversation result (ADC1BUF0) and print it
    printInt(ADC1BUF0, 16 | 3 << 16);
    putChar('\r');

    // Start A/D conversation
    AD1CON1bits.ASAM = 1;

    IFS1bits.AD1IF = 0;         // Reset AD1IF flag
}
