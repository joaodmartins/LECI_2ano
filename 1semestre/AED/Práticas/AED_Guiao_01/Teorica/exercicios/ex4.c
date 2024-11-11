#include <stdio.h>

int main (void) {
    char str[] = "Hello, World!";
    char *ptr = str;
    printf("String characters using pointers arithmetic:\n");
    while(*ptr != '\0') {
        printf("%c", *ptr);
        ptr++;
    }
    printf("\n");
    return 0;
}