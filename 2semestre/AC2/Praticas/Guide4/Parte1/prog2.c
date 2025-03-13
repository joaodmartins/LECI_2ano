#include <detpic32.h>

void delay(int ms);

int main(void) {
    LATE = LATE & 0xFF87;       // 1111 1111 1000 0111
    TRISE = TRISE & 0xFF87;
    
    int count = 0;

    while(1) {
        LATE = (LATE & 0xFF87) | count << 3;

        resetCoreTimer(); 
        while( readCoreTimer() < 4347826 );
        count = (count + 1) % 10;
    }
}
