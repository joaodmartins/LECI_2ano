#include <stdio.h>
int comparacoes;

int contar_elementos(int array[], int n){
    int count = 0;

    for (int i = 1; i < n - 1; i++) {
        comparacoes++;
        if (array[i] == array [i - 1] + array[i + 1]) {
            count++;
        }
    }

    return count;
}

int main (void) {

    int a1 [10] = {1,2,3,4,5,6,7,8,9,10};
    int a2 [10] = {1,2,1,4,5,6,7,8,9,10};
    int a3 [10] = {1,2,1,3,2,6,7,8,9,10};
    int a4 [10] = {0,2,2,0,3,3,0,4,4,0};
    int a5 [10] = {0,0,0,0,0,0,0,0,0,0};

    comparacoes = 0;
    int resultado = contar_elementos(a1, 10);
    printf("a1: resultado - %d comparacoes - %d\n", resultado, comparacoes);

    comparacoes = 0;
    resultado = contar_elementos(a2, 10);
    printf("a2: resultado - %d comparacoes - %d\n", resultado, comparacoes);

    comparacoes = 0;
    resultado = contar_elementos(a3, 10);
    printf("a3: resultado - %d comparacoes - %d\n", resultado, comparacoes);

    comparacoes = 0;
    resultado = contar_elementos(a4, 10);
    printf("a4: resultado - %d comparacoes - %d\n", resultado, comparacoes);

    comparacoes = 0;
    resultado = contar_elementos(a5, 10);
    printf("a5: resultado - %d comparacoes - %d\n", resultado, comparacoes);

    return 0;
}