#include <stdio.h>
#include <math.h>

int main(void) {
    int cubos[10];
    for (int i = 0; i < 10; i++) {
        cubos[i] = i * i * i;
    };

    int contagem_operacoes = 0;

    printf("Numeros de Armstrong de 3 algarismos: \n");
    for (int num = 100; num < 1000; num++) {
        int centenas = num / 100;
        int dezenas = (num / 10) % 10;
        int unidades = num % 10;

        int soma_cubos = cubos[centenas] + cubos[dezenas] + cubos[unidades];
        contagem_operacoes+= 2;

        if (soma_cubos == num) {
            printf("%d = %d + %d + %d\n", soma_cubos, cubos[centenas], cubos[dezenas], cubos[unidades]);
        }
    }
    printf("Numero de divisoes inteiras executadas: %d", contagem_operacoes);
    return 0;
}

