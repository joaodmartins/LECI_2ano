#include <stdio.h>

int main(void) {
    int my_array[3] = {1, 2, 3};
    int* p = my_array;

    for(int i = 0; i < 3; i++) {
        printf("%d\n", *p);
        p = p + 1;
    }
}