#include <stdio.h>
#define SIZE 20

long unsigned int Del_Cache[SIZE][SIZE];

void initialize_cache(void) {
    for (unsigned int i = 0; i < SIZE; i++) {
        for (unsigned int j = 0; j < SIZE; j++) {
            Del_Cache[i][j] = 0;
        }
    }
}

long unsigned int delanoy_memo(unsigned int m, unsigned int n) {
    if(Del_Cache[m][n] != 0) return Del_Cache[m][n];

    long unsigned int r;
    if ((m == 0) || (n == 0)) {
        r = 1;
    } else {
        r = delanoy_memo(m - 1, n) + delanoy_memo(m - 1, n - 1) + delanoy_memo(m, n - 1);
    }

    Del_Cache[m][n] = r;
    return r;
}

int main(void) {
    int m, n;
    printf("Digite os valores de m e n: ");
    scanf("%d %d", &m, &n);
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n ; j++) {
            printf("%12d", delanoy_memo(i, j));
        }
        printf("\n");
    }
    return 0;
}