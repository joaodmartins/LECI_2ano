#include <detpic32.h>

void delay(int ms);

int main(void){
    LATB = LATB & 0x80FF;    // 1000 0000 1111 1111
    LATD = LATD & 0xFF9F;    // 1111 1111 1001 1111

    TRISB = TRISB & 0x80FF;
    TRISD = TRISD & 0xFF9F;

    while(1) {
        char ch = getChar();

        if(ch == 'a') LATB = (LATB & 0x80FF) | (1 << 8);
        if(ch == 'b') LATB = (LATB & 0x80FF) | (1 << 9); 
        if(ch == 'c') LATB = (LATB & 0x80FF) | (1 << 10);
        if(ch == 'd') LATB = (LATB & 0x80FF) | (1 << 11);   
        if(ch == 'e') LATB = (LATB & 0x80FF) | (1 << 12);
        if(ch == 'f') LATB = (LATB & 0x80FF) | (1 << 13);
        if(ch == 'g') LATB = (LATB & 0x80FF) | (1 << 14);

        LATD = (LATD & 0xFF9F) | (1 << 5);
    }

    return 0;
}