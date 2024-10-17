#include <stdio.h>

int multiplicacoes;
int divisoes;

int verifica (double a[], int n) {
    double r = a[1] / a[0];
    divisoes++;

    for (int i = 2; i < n; i++) {
        double ai = r * a[i - 1];
        multiplicacoes++;

        if (a[i] != ai) {
            return 0;
        }
    }

    return 1;
}

int main(void) {
    double seq1 [10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    double seq2 [10] = {1, 2, 4, 4, 5, 6, 7, 8, 9, 10};
    double seq3 [10] = {1, 2, 4, 8, 5, 6, 7, 8, 9, 10};
    double seq4 [10] = {1, 2, 4, 8, 16, 6, 7, 8, 9, 10};
    double seq5 [10] = {1, 2, 4, 8, 16, 32, 7, 8, 9, 10};
    double seq6 [10] = {1, 2, 4, 8, 16, 32, 64, 8, 9, 10};
    double seq7 [10] = {1, 2, 4, 8, 16, 32, 64, 128, 9, 10};
    double seq8 [10] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 10};
    double seq9 [10] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};

    multiplicacoes = 0;
    divisoes = 0;
    int resultado = verifica(seq1, 10);
    printf("Sequencia 1: Resultado = %d, Multiplicações = %d, Divisões = %d\n", resultado, multiplicacoes, divisoes);

    multiplicacoes = 0;
    divisoes = 0;
    resultado = verifica(seq2, 10);
    printf("Sequencia 2: Resultado = %d, Multiplicações = %d, Divisões = %d\n", resultado, multiplicacoes, divisoes);

    multiplicacoes = 0;
    divisoes = 0;
    resultado = verifica(seq3, 10);
    printf("Sequencia 3: Resultado = %d, Multiplicações = %d, Divisões = %d\n", resultado, multiplicacoes, divisoes);
    
    multiplicacoes = 0;
    divisoes = 0;
    resultado = verifica(seq4, 10);
    printf("Sequencia 4: Resultado = %d, Multiplicações = %d, Divisões = %d\n", resultado, multiplicacoes, divisoes);

    multiplicacoes = 0;
    divisoes = 0;
    resultado = verifica(seq5, 10);
    printf("Sequencia 5: Resultado = %d, Multiplicações = %d, Divisões = %d\n", resultado, multiplicacoes, divisoes);

    multiplicacoes = 0;
    divisoes = 0;
    resultado = verifica(seq6, 10);
    printf("Sequencia 6: Resultado = %d, Multiplicações = %d, Divisões = %d\n", resultado, multiplicacoes, divisoes);

    multiplicacoes = 0;
    divisoes = 0;
    resultado = verifica(seq7, 10);
    printf("Sequencia 7: Resultado = %d, Multiplicações = %d, Divisões = %d\n", resultado, multiplicacoes, divisoes);

    multiplicacoes = 0;
    divisoes = 0;
    resultado = verifica(seq8, 10);
    printf("Sequencia 8: Resultado = %d, Multiplicações = %d, Divisões = %d\n", resultado, multiplicacoes, divisoes);

    multiplicacoes = 0;
    divisoes = 0;
    resultado = verifica(seq9, 10);
    printf("Sequencia 9: Resultado = %d, Multiplicações = %d, Divisões = %d\n", resultado, multiplicacoes, divisoes);
    return 0;
}