#include <stdio.h>

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void selectionSortStepByStep(int a[], int step, int n) {
    int indMax = 0;
    for (int i = 1; i < n - step; i++) {
        if (a[i] >= a[indMax]) {
            indMax = i;
        }
    }
    if (indMax != n - step - 1) {
        swap(&a[indMax], &a[n - step - 1]);
    }
}

void printArray(int a[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i < n - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void) {
    int a1[6] = {6, 5, 4, 3, 2, 1};

    printf("a1 original: ");
    printArray(a1, 6);

    for (int step = 0; step < 5; step++) {
        printf("a1 step %d: ", step + 1);
        selectionSortStepByStep(a1, step, 6);
        printArray(a1, 6);
    }

    return 0;
}