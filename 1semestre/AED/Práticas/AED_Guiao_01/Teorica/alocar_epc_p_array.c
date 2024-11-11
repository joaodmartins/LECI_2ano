#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int* a = NULL;

    a = (int*)malloc(3 * sizeof(int));

    if(a == NULL){
        exit(1);
    }

    a[0] = 99;
    a[1] = 100;
    a[2] = 101;

    printf("{%d, %d, %d}", a[0], a[1], a[2]);

    free(a); 
}