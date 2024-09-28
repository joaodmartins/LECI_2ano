#include <stdio.h>

void Permute(int* a, int* b, int* c) {
    int d = *a;
    *a = *b;
    *b = *c;
    *c = d;
}

int main(void) {
    int a, b, c;

    printf("a: ");
    scanf("%d", &a);
    printf("b: ");
    scanf("%d", &b);
    printf("c: ");
    scanf("%d", &c);

    printf("Before: a = %d, b = %d, c = %d\n", a, b, c);
    Permute(&a, &b, &c);
    printf("After: a = %d, b = %d, c = %d\n", a, b, c);
    return 0;
}