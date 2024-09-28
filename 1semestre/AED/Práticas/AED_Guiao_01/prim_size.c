#include <stdio.h>

int main() {
    printf("Tamanhos dos tipos primitivos em C:\n");
    printf("void*: %zu bytes\n", sizeof(void*));
    printf("void: %zu bytes\n", sizeof(void));
    printf("char: %zu bytes\n", sizeof(char));
    printf("short: %zu bytes\n", sizeof(short));
    printf("int: %zu bytes\n", sizeof(int));
    printf("long: %zu bytes\n", sizeof(long));
    printf("long long: %zu bytes\n", sizeof(long long));
    printf("float: %zu bytes\n", sizeof(float));
    printf("double: %zu bytes\n", sizeof(double));

    return 0;
}
