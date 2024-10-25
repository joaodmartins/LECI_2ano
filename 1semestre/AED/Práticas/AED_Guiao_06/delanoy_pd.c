#include <stdio.h>

long unsigned int delanoy_pd(unsigned int m, unsigned int n) {
    if (m == 0 || n == 0) {
        return 1;
    } 

    long unsigned int comb[m + 1][n + 1];

    // for escreve a linha de indice 0
    for (unsigned int j = 0; j <= n; j++) {
        comb[0][j] = 1;
    }
    for (unsigned int i = 1; i <= m; i++) {
        comb[i][0] = 1;
        for (unsigned int j = 1; j <= n; j++) {
            comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1] + comb[i][j - 1];
        }
    }
    return comb[m][n];
}

int main(void) {
    int m, n;
    printf("Digite os valores de m e n: ");
    scanf("%d %d", &m, &n);
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n ; j++) {
            printf("%12d", delanoy_pd(i, j));
        }
        printf("\n");
    }
    return 0;
}