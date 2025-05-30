#include <detpic32.h>

int main(void) {
    TRISD = (TRISD & 0xFFFB);


    while(1) {}
    return 0;
}


void _int_(27) isr_adc(void) {
    
}

void _int_() isr_T5(void) {

}