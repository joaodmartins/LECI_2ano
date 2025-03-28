#include <detpic32.h>

void send2displays(unsigned char value);
unsigned char toBcd(unsigned char vlaue);
void delay(int ms);

volatile unsigned char voltage = 0;
int smp = 8;

int main(void)
{
    unsigned int cnt = 0;

    // Configure all (digital I/O, analog input, A/D module, interrupts)
    TRISBbits.TRISB4 = 1;     // RB4 digital output disconnected
    AD1PCFGbits.PCFG4 = 0;    // RB4 configured as analog input
    AD1CON1bits.SSRC = 7;     // Conversion trigger selection bits: in this mode an internal counter ends sampling and starts conversion
    AD1CON1bits.CLRASAM = 1;  // Stop conversions when the 1st A/D converter interrupt is generated. At the same time,
                              // hardware clears the ASAM bit
    AD1CON3bits.SAMC = 16;    // Sample time is 16 TAD (TAD = 100 ns)
    AD1CON2bits.SMPI = smp - 1; // Interrupt is generated after 0 samples
    AD1CHSbits.CH0SA = 4;     // input analog channel 4
    AD1CON1bits.ON = 1;       // Enable A/D converter

    // Configure interrupt system
    IPC6bits.AD1IP = 2; // configure priority of A/D interrupts
    IFS1bits.AD1IF = 0; // clear A/D interrupt flag
    IEC1bits.AD1IE = 1; // enable A/D interrupts

    // Configure displays
    TRISB = TRISB & 0x80FF; // RB14  to RB8 as output
    TRISD = TRISD & 0xFF9F; // Displays hight/low as output

    EnableInterrupts(); // Global interrupt Enable

    while (1)
    {
        if (cnt == 0)
        {                         // 0, 200 ms, 400 ms, ... (5 samples/second)
            AD1CON1bits.ASAM = 1; // Start A/D conversation
        }

        send2displays(voltage);

        cnt = (cnt + 1) % 20;

        // Wait 10 ms
        delay(10);
    }
    return 0;
}

void _int_(27) isr_adc(void) // Replace VECTOR by the A/D vector
                             // number - see "PIC32 family data
                             // sheet" (pages 74-76)
                             // ADC = 27
{
    // Read 8 samples (ADC1BUF0, ..., ADC1BUF7) and calculate average
    int *p = (int *) & ADC1BUF0;
    int average = 0;
    int i;
    for(i = 0; i < smp; i++) {
        average += p[i * 4];
    }

    average = average / smp;
    // Calculate voltage amplitude
    voltage = (average * 33 + 511) / 1023;
    // Convert voltage amplitude to decimal and store the result in the global variable "voltage"
    voltage = toBcd(voltage);
    // Reset AD1IF flag
    IFS1bits.AD1IF = 0;
    // Read conversation result (ADC1BUF0) and print it
    printInt(ADC1BUF0, 16 | 3 << 16);
    putChar('\r');
}

void send2displays(unsigned char value)
{
    static const char disp7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    static char displayFlag = 0; // static variable: doesn't loose its
                                 // value between calls to function
    int digit_low = value & 0x0F;
    int digit_high = value >> 4;
    // if "displayFlag" is 0 then send "digit_low" to display_low
    if (displayFlag == 0)
    {
        LATD = (LATD & 0xFF9F);
        LATD = (LATD | 0x0020);
        LATB = (LATB & 0x80FF) | (disp7Scodes[digit_low] << 8);
    }
    // else send "digit_high" to didplay_high
    else
    {
        LATD = (LATD & 0xFF9F);
        LATD = (LATD | 0x0040);
        LATB = (LATB & 0x80FF) | (disp7Scodes[digit_high] << 8);
    }
    // toggle "displayFlag" variable
    displayFlag = !displayFlag;
}

unsigned char toBcd(unsigned char value) {
    return ((value / 10) << 4) + (value % 10);
}

void delay(int ms)
{
    resetCoreTimer();
    while (readCoreTimer() < (20000 * ms));
}
