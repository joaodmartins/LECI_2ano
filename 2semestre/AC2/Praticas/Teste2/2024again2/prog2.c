#include <detpic32.h>

int main(void) {
    while(1) {
        AD1CON1bits.ASAM = 1;
        while( IFS1bits.AD1IF == 0 );

        int i, media = 0;
        int *P = (int *) (&ADC1BUF0);
        for(i = 0; i < 2; i++) {
            media += p[i * 4];
        }
        media = media / 2;
        temp = (media * 50 + 511) / 1023 + 7
        IFS1bits.AD1IF = 0
    }
}