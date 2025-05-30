#include <detpic32.h>

unsigned char to_bcd(unsigned char value);

int main(void) {
    TRISB = (TRISB & 0x80FF);
    TRISD = (TRISD & 0xFF9F);

    // Configure Timer 1 (1, 8, 64, 256)
    // 10Hz
    // k_prescaler = 20MHz / (65535 + 1) * fout(10Hz) = 30 -> 64
    // Prescaler 1:64 -> 2
    // Fout = 20MHz / (64 * (x + 1)) = 10Hz
    // x = (20MHz / 10 * 64) - 1 = 31 249

    T1CONbits.TCKPS = 2;   // 1:64 prescaler
    PR2 = 31249;         // Fout = 20MHz / (64 * (31249 + 1)) = 10Hz
    TMR1 = 0;            // Clear timer T1 count register

    IPC1bits.T1IP = 2;      // Set priority for timer T1 interrupt
    IEC0bits.T1IE = 1;      // Enable timer T1 interrupt
    IFS0bits.T1IF = 0;      // Reset timer T1 interrupt flag 

    // Configure Timer 2 (1, 2, 4, 8, 16, 32, 64, 256)
    // 50Hz
    // k_prescaler = 20MHz / ((65535 +1) * fout(50Hz)) = 3 276 800 = 6,10 -> 8
    // Prescaler 1:8 -> 3
    // Fout = 20MHz / (8 * (x + 1)) = 50Hz
    // x = 20Mhz / (50 * 8) - 1 = 49 999

    T2CONbits.TCKPS = 3;   // 1:8 prescaler
    PR2 = 49999;           // Fout = 20MHz / (8 * (49999 + 1)) = 50Hz
    TMR2 = 0;              // Clear timer T2 count register

    IPC2bits.T2IP = 3;      // Set priority for timer T2 interrupt
    IEC0bits.T2IE = 1;      // Enable timer T2 interrupt
    IFS0bits.T2IF = 0;      // Reset timer T2 interrupt flag

    T1CONbits.TON = 1;   // Enable timer T1
    T2CONbits.TON = 1;     // Enable timer T2

    EnableInterrupts();    // Global interrupt enable

    while(1) {
        IdleMode();
    }
    return 0;
}

void _int_(4) isr_T1(void) {
    if (++count >= 100) {
        count = 0;
    }
    IFS0bits.T1IF = 0;  // Reset T1IF flag
}

void _int_(8) isr_T2(void) {
    static const char d7Sc[] = {
        0x3F, 0x06, 0x5B, 0x4F,
        0x66, 0x6D, 0x7D, 0x07,
        0x7F, 0x6F, 0x77, 0x7C,
        0x39, 0x5E, 0x79, 0x71
    };

    static char dis_ctl = 0;

    if(disp_ctl) {
        LATB = (LATB & 0x80FF) | d7Sc[to_bcd(count) >> 4] << 8;
        LATDbits.LATD6 = 1;
        LATDbits.LATD5 = 0;
    } else {
        LATB = (LATB & 0x80FF) | d7Sc[to_bcd(count) & 0x0F] << 8;
        LATDbits.LATD6 = 0;
        LATDbits.LATD5 = 1;
    }

    disp_ctl = !disp_ctl;  // Toggle display control
    IFS0bits.T2IF = 0;  // Reset T2IF flag
}

unsigned char to_bcd(unsigned char value) {
    return ((value / 10) << 4) + (value % 10);
}