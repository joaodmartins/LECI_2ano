#include <stdio.h>

int main(void){
    int i = 10;
    printf("int i = %d\n", i);
    int* ptr_i = &i;
    printf("ptr_i = %d\n", &i);
    printf("*ptr_i = %d\n", *ptr_i);
    int* another_ptr = ptr_i;
    printf("another_ptr = %d\n", ptr_i);
    printf("*another_ptr = %d\n", *another_ptr);
    *ptr_i = 5;
    printf("*ptr_i = %d\n", *ptr_i);
    *another_ptr = 20;
    printf("*another_ptr = %d\n", *another_ptr);

    return 0;
}