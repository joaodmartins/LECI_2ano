#include <stdio.h>

int maior(int a, int b, int c, int d) {
    int maior = a;
    if (b > maior) {
        maior = b;
    }
    if (c > maior) {
        maior = c;
    }
    if (d > maior) {
        maior = d;
    }
    return maior;
}

int main (void) {
    int a, b, c, d;
    printf("Introduza quatro numeros: ");
    scanf("%d %d %d %d", &a, &b, &c, &d);
    printf("O maior numero e: %d", maior(a, b, c, d));

    return 0;
}