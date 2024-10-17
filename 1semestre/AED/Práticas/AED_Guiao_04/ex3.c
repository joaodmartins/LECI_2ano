#include <stdio.h>

int comparacoes;

int contarTernos(int array[], int n) {
    int count = 0;

    for (int k = 2; k < n; k++) {
        for (int j = 1; j < k; j++) {
            for (int i = 0; i < j; i++) {
                comparacoes++;
                if(array[k] == array[i] + array[j]) {
                    count++;
                }
            }
        }
    }
    return count;
}

int main(void) {

    int seq1[] = {1, 2, 3, 4, 5};

    int seq2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    int seq3[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

    int seq4[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

    int seq5[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};

    int seq6[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};

    int seq7[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40};

    int seq8[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50};

    comparacoes = 0;
    int resultado = contarTernos(seq1, 5);
    printf("Sequencia 1: Resultado = %d, Comparacoes = %d\n", resultado, comparacoes);

    comparacoes = 0;
    resultado = contarTernos(seq2, 10);
    printf("Sequencia 2: Resultado = %d, Comparacoes = %d\n", resultado, comparacoes);

    comparacoes = 0;
    resultado = contarTernos(seq3, 15);
    printf("Sequencia 3: Resultado = %d, Comparacoes = %d\n", resultado, comparacoes);

    comparacoes = 0;
    resultado = contarTernos(seq4, 20);
    printf("Sequencia 4: Resultado = %d, Comparacoes = %d\n", resultado, comparacoes);

    comparacoes = 0;
    resultado = contarTernos(seq5, 25);
    printf("Sequencia 5: Resultado = %d, Comparacoes = %d\n", resultado, comparacoes);

    comparacoes = 0;
    resultado = contarTernos(seq6, 30);
    printf("Sequencia 6: Resultado = %d, Comparacoes = %d\n", resultado, comparacoes);

    comparacoes = 0;
    resultado = contarTernos(seq7, 40);
    printf("Sequencia 7: Resultado = %d, Comparacoes = %d\n", resultado, comparacoes);

    comparacoes = 0;
    resultado = contarTernos(seq8, 50);
    printf("Sequencia 8: Resultado = %d, Comparacoes = %d\n", resultado, comparacoes);

    return 0;
}