#include <stdio.h>

int main(void) {
    int a = 10;
    int b = 99;
    printf("Value of a + b is: %d\n", a + b);

    int* p_a = &a;
    int* p_b = &b;
    int sum = *p_a + *p_b;

    *p_a = 1000;
    *p_b = 9999;

    printf("Value of sum is: %d\n", sum);
    printf("Value of a + b is: %d\n", a + b);

    return 0;
}