#include <detpic32.h>

int main(void) {
    TRISE = (TRISE & 0xFFFD);
    TRISE = (TRISE | 0x0001);

    while(1) {
        value = PORTE & 0x0001;
        value = value ^ 0x0001;

        LATE = (LATE & 0xFFFD) | (value << 1);
    }
    return 0;
}