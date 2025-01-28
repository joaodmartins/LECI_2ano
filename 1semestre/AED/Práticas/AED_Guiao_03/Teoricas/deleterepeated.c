#include <stdio.h>

int eliminateRepeated(int *a, int n) {
    if (n == 0) return 0;
    
    int k = 0; // Índice para armazenar elementos únicos
    for (int i = 0; i < n; i++) {
        if (i == 0 || a[i] != a[i - 1]) { // Apenas adiciona se for o primeiro ou diferente do anterior
            a[k++] = a[i];
        }
    }

    return k;
}

int main() {
    int a[] = {1, 2, 2, 2, 3, 4, 5, 6, 6, 7};
    int n = sizeof(a) / sizeof(a[0]);
    
    int newSize = eliminateRepeated(a, n);
    
    printf("Vetor sem repetidos: ");
    for (int i = 0; i < newSize; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    
    return 0;
}