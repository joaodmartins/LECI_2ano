#include <stdio.h>

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void selectionSort(int a[], int n) {
    for (int k = n - 1; k > 0; k--) {
        int indMax = 0;
        for (int i = 1; i <= k; i++) {
            if (a[i] >= a[indMax]) {
                indMax = i;
            }
        }
        if (indMax != k) {
            swap(&a[indMax], &a[k]);
        }
    }
}

void printArray(int a[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i < n - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void) {
    int a1 [10] = {1,2,3,4,5,6,7,8,9,10};
    int a2 [10] = {10,3,4,5,6,7,8,9,1,2};
    int a3 [10] = {3,5,9,8,10,1,6,4,2,7};
    int a4 [10] = {10,9,8,7,6,5,4,3,2,1};

    printf("a1 before: ");
    printArray(a1, 10);
    printf("a1 after: ");
    selectionSort(a1, 10);
    printArray(a1, 10);

    printf("a2 before: ");
    printArray(a2, 10);
    printf("a2 after: ");
    selectionSort(a2, 10);
    printArray(a2, 10);

    printf("a3 before: ");
    printArray(a3, 10);
    printf("a3 after: ");
    selectionSort(a3, 10);
    printArray(a3, 10);

    printf("a4 before: ");
    printArray(a4, 10);
    printf("a4 after: ");
    selectionSort(a4, 10);
    printArray(a4, 10);
    return 0;
}