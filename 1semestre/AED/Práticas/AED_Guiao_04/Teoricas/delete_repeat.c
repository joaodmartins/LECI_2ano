#include <stdio.h>

int delete_repeated(int *a, int n) {
    int k = 0;
    for(int i = 0; i < n; i++) {
        if(i == 0 || a[i] != a[i - 1]) {
            a[k++] = a[i];
        }
    }
    return k;
}

void print_array(int *a, int n) {
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
    int a [9] =  {1, 2, 3, 4, 4, 4, 5, 6, 7};

    int new_size = delete_repeated(a, 9);

    print_array(a, new_size);
}