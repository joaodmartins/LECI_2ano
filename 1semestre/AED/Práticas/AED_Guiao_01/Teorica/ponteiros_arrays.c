#include <stdio.h>

int main(void) {
    int my_array[3] = {1, 2, 3};
    printf("My array: {%d, %d, %d}\n", my_array[0], my_array[1], my_array[2]);
    
    int* p_my_array = my_array;

    my_array[0] = 10;
    printf("My array after my_array[0] = 10: {%d, %d, %d}\n", my_array[0], my_array[1], my_array[2]);

    *my_array = 20;
    printf("My array after *my_array = 20: {%d, %d, %d}\n", my_array[0], my_array[1], my_array[2]);

    *p_my_array = 30;
    printf("My array after *p_my_array = 30: {%d, %d, %d}\n", my_array[0], my_array[1], my_array[2]);
    
    return 0;
}