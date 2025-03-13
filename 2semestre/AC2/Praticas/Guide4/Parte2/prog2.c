#include <detpic32.h>

void delay(int ms);

int main(void){
    LATB = LATB & 0x80FF;    // 1000 0000 1111 1111
    LATD = LATD & 0xFF9F;    // 1111 1111 1001 1111

    TRISB = TRISB & 0x80FF;
    TRISD = TRISD & 0xFF9F;

    while(1) {
        char ch = getChar();

        if(ch >= 'a' && ch <= 'g') {
            ch = ch - 'a';
            LATB = (LATB & 0x80FF) | 1 << (ch + 8);
        }

        LATD = (LATD & 0xFF9F) | (1 << 5);
    }

    return 0;
}