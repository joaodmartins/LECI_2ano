#include <stdio.h>

int sum(int a, int b) {
    return a + b;
}

int p_sum(int* p_a, int* p_b) {
    return (*p_a) + (*p_b);
}

int main(void) {
    int m = 10;
    int n = 20;

    int res = sum(m, n);
    printf("res = %d\n", res);

    res = p_sum(&m, &n);
    printf("res = %d", res);
}