#include <stdio.h>

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void bubbleSort(int a[], int n) {
    int k = n; int stop = 0; 
    while(stop == 0) {
        stop = 1; k--;
        for(int i = 0; i < k; i++) {
            if(a[i] > a[i + 1]) {
                swap(&a[i], &a[i + 1]);
                stop = 0;
            }
        }
    }
}

void printArray(int a[], int n) {
    printf("[");
    for(int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if(i < n - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void) {
    int a1[5] = {7,2,6,4,3};

    printf("a1 original: ");
    printArray(a1, 5);
    bubbleSort(a1, 5);
    printf("a1 sorted: ");
    printArray(a1, 5);


    return 0;
}