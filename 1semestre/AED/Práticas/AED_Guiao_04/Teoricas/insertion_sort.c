#include <stdio.h> 

void insertElement(int sorted[], int n, int elem) {
    int i;
    for(i = n - 1; (i >= 0) && (elem < sorted[i]); i--) {
        sorted[i + 1] = sorted[i];
    }
    sorted[i + 1] = elem;
}

void insertionSort(int a[], int n) {
    for(int i = 1; i < n; i++) {
        if(a[i] < a[i - 1]) {
            insertElement(a, i, a[i]);
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

    printf("a1 before: ");
    printArray(a1, 5);
    insertionSort(a1, 5);
    printf("a1 sorted: ");
    printArray(a1, 5);

    return 0;
}


