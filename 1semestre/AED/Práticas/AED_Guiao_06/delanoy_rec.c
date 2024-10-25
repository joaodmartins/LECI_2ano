#include <stdio.h>

int delanoy_pd(unsigned int m, unsigned int n) {
    if (m == 0 || n == 0) {
        return 1;
    } 
    return delanoy_rec(m - 1, n) + delanoy_rec(m - 1, n - 1) + delanoy_rec(m, n - 1);
}

int main(void) {
    int m, n;
    printf("Digite os valores de m e n: ");
    scanf("%d %d", &m, &n);
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n ; j++) {
            printf("%12d", delanoy_rec(i, j));
        }
        printf("\n");
    }
    return 0;
}