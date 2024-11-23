#include <stdio.h>

int maior(int a, int b, int c, int d) {
    int maior;
    if (a > b) {
        if (a > c) {
            if (a > d) {
                maior = a;
            } else {
                maior = d;
            }
        } else {
            if (c > d) {
                maior = c;
            } else {
                maior = d;
            }
        }
    } else  {
        if (b > c) {
            if (b > d) {
                maior = b;
            } else {
                maior = d;
            }
        } else {
            if (c > d) {
                maior = c;
            } else {
                maior = d;
            }
        }
    }
    return maior;
}

int main (void) {
    int a;
    int b;
    int c;
    int d;
    printf("Introduza quatro numeros: ");
    scanf("%d %d %d %d", &a, &b, &c, &d);
    printf("O maior numero e: %d", maior(a, b, c, d));

    return 0;
}