#include <detpic32.h>

int main(void) {
    TRISE = TRISE & 0xFFF0; // Configure RE0-RE3 as outputs (0)

    TRISB = TRISB & 0x80FF; // Configure RB8-RB15 as outputs (0)
    TRISD = TRISD & 0xFF9F; // Configure RD5-RD6 as outputs (0)

    // -----------------------------------
    // TIMER 2 (1, 2, 4, 8, 16, 32, 64, 256)
    // 100Hz
    // k_prescaler = 20Mhz / (65535 + 1) * fout(100Hz) = 3 -> 4
    // Prescaler 1:4 -> 2
    // Fout = 20MHz / (4 * (x + 1)) = 100Hz
    // x = (20MHz / 100 * 4) - 1 = 49 999
    // PR2 = x = 49999
    // -----------------------------------

    T2CONbits.TCKPS = 2;    // 1:4 prescaler
    PR2 = 49999;            // Fout = 20MHz / (4 * (49999 + 1)) = 100Hz
    TMR2 = 0;               // Clear timer T2 count register
    T2CONbits.TON = 1;      // Enable timer T2

    IPC2bits.T2IP = 2;        // Set priority for timer T2 interrupt
    IEC0bits.T2IE = 1;        // Enable timer T2 interrupt
    IFS0bits.T2IF = 0;        // Reset timer T2 interrupt flag

    EnableInterrupts();       // Global interrupt enable

    while(1) {
        switch (inkey()) {
            case 0x00:
                continue;
            case '0':
                LATE = (LATE & 0xFFF0) | 0x0001;
                hi_digit = 0x3F;
                lo_digit = 0x3F;
                break;
            case '1':
                LATE = (LATE & 0xFFF0) | 0x0002;
                hi_digit = 0x3F;
                lo_digit = 0x06;
                break;
            case '2':
                LATE = (LATE & 0xFFF0) | 0x0003;
                hi_digit = 0x3F;
                lo_digit = 0x5B;
                break;
            case '3':
                LATE = (LATE & 0xFFF0) | 0x0004;
                hi_digit = 0x3F;
                lo_digit = 0x4F;
                break;
            default:
                reset_routine();
                while (inkey() != 0) {};
                break;
        }
    }
    return 0;
}

void reset_routine(void) {
    resetCoreTimer();
    LATE = (LATE | 0x000F);
    hi_digit = 0x71;
    lo_digit = 0x71;
    while(readCoreTimer() < 20000000)
    LATE = (LATE & 0xFFF0);
    hi_digit = 0x00;
    lo_digit = 0x00;
}

void _int_(8) isr_T2(void) { // Timer 2 interrupt service routine
    static unsigned short int disp_ctl = 1;

    if (dis_ctl) {
        LATB = (LATB & 0x80FF) | (hi_digit << 8);
        LATDbits.LATD6 = 1;
        LATDbits.LATD5 = 0;
    } else {
        LATB = (LATB & ox80FF) | (lo_digit << 8);
        LATDbits.LATD6 = 0;
        LATDbits.LATD5 = 1;
    }

    disp_ctl = !disp_ctl; // Toggle display control
    IFS0bits.T2IF = 0; // Reset timer T2 interrupt flag
}

