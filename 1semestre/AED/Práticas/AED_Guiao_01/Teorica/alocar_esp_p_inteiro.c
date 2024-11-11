#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int* ptr = NULL;

    ptr = (int*)malloc(sizeof(int));

    if(ptr == NULL) {
        exit(1);
    }

    *ptr = 99;
    printf("%d\n", *ptr);

    free(ptr);
    return 0;
}