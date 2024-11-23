#include <stdio.h>

void merge(int* A, int* tmpA, int lPos, int rPos, int rEnd) {
    int lEnd = rPos - 1;
    int tmpPos = lPos;
    int nElements = rEnd - lPos + 1;

    while (lPos <= lEnd && rPos <= rEnd) {
        if(A[lPos] <= A[rPos]) {
            tmpA[tmpPos++] = A[lPos++];
        } else {
            tmpA[tmpPos++] = A[rPos++];
        }
    }

    for(int i = 0; i < nElements; i++, rEnd--) {
        A[rEnd] = tmpA[rEnd];
    }
}

void mergeSort(int* A, int* tmpA, int left, int right) {
    if(left < right) {
        int center = (left + right) / 2;

        mergeSort(A, tmpA, left, center);
        mergeSort(A, tmpA, center + 1, right);
        merge(A, tmpA, left, center + 1, right);
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
    int a2[5];

    printf("a1 before: ");
    printArray(a1, 5);
    mergeSort(a1, a2, 0, 4);
    printf("a1 sorted: ");
    printArray(a1, 5);

    return 0;
}