#include <stdio.h>

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void bubble_sort(int a[], int n) {
    int stop = 0, k = n;
    while(stop == 0) {
        stop = 1;
        k--;
        for (int i = 0; i < k; i++) {
            if(a[i] > a[i + 1]) {
                swap(&a[i], &a[i + 1]);
                stop = 0;
            }
        }
    }
}

void print_array(int a[], int n) {
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
    int a1 [6] = {3, 6, 1, 4, 2, 5};

    printf("a1 before: ");
    print_array(a1, 6);
    printf("a1 after: ");
    bubble_sort(a1, 6);
    print_array(a1, 6);

    return 0;
}