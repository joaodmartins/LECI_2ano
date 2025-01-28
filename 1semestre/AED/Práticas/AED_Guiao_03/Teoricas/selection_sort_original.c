#include <stdio.h>

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void selection_sort(int a[], int n) {
    for(int k = n - 1; k > 0; k--) {
        int indMax = 0;
        for(int i = 1; i <= k; i++) {
            if(a[i] > a[indMax]) {
                indMax = i;
            }
        }
        if(indMax != k) {
            swap(&a[indMax], &a[k]);
        }
    }
}

void print_array(int a[], int n) {
    printf("[");
    for(int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if(i < n-1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void) {
    int a1 [6] = {3, 2, 6, 5, 1, 4};

    printf("a1 before: ");
    print_array(a1, 6);
    printf("a1 after: ");
    selection_sort(a1, 6);
    print_array(a1, 6);

    return 0;
}