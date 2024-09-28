#include <stdio.h>
#include <math.h>

int main() {
    int n;

    printf("Digite o número de linhas da tabela: ");
    scanf("%d", &n);

    printf("%-10s %-10s %-15s\n", "Número", "Quadrado", "Raiz Quadrada");
    printf("-------------------------------------------\n");

    for (int i = 1; i <= n; i++) {
        int quadrado = i * i;
        double raizQuadrada = sqrt(i);

        printf("%-10d %-10d %-15f\n", i, quadrado, raizQuadrada);
    }

    return 0;
}