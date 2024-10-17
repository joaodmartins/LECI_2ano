#include <stdio.h>

void calcular_fatoriais(int fatoriais[]) {
    fatoriais[0] = 1;
    int fatorial = 1;
    for (int i = 1; i < 10; i++) {
        fatorial *= i;
        fatoriais[i] = fatorial;
    }
}

int soma_fatoriais_dos_digitos(int num, int fatoriais[]) {
    int soma_fatoriais = 0;
    while (num > 0) {
        int digito = num % 10;
        soma_fatoriais += fatoriais[digito];
        num /= 10;
    }
    return soma_fatoriais;
}

int main(void) {
    int fatoriais[10];
    calcular_fatoriais(fatoriais);

    printf("Factoriões menores que 1.000.000:\n");
    for (int num = 1; num < 1000000; num++) {
        int soma_fatoriais = soma_fatoriais_dos_digitos(num, fatoriais);

        if (soma_fatoriais == num) {
            printf("%d\n", num);
        }
    }
    return 0;
}