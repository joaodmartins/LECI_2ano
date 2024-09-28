#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

// Display the contents of array a with n elements
// Pre-Conditions: a != NULL and n > 0
// Example of produced output: Array = [ 1.00, 2.00, 3.00 ]
void DisplayArray(double* a, size_t n) { 
    assert(a != NULL);
    assert(n > 0);
    
    printf("Array = [ ");
    for (size_t i = 0; i < n; i++) {
        if (i > 0) {
            printf(", ");
        }
        printf("%.2f", a[i]);
    }
    printf("]\n");
}

// Allocate and return a new array with (size_1 + size_2) elements
// which stores the elements of array_1 followed by the elements of array_2
// Pre-Conditions: array_1 != NULL and array_2 != NULL
// Pre-Conditions: size_1 > 0 and size_2 > 0
// Return NULL if memory allocation fails
double* Append(double* array_1, size_t size_1, double* array_2, size_t size_2) {   
    assert(array_1 != NULL);
    assert(array_2 != NULL);
    assert(size_1 > 0);
    assert(size_2 > 0);

    double* new_array = malloc((size_1 + size_2)* sizeof(double));
    if (new_array == NULL) {
        printf("Falhou a alocação de memoria \n");
        return NULL;
    }

    size_t j = 0;

    for (size_t i = 0; i < size_1; i++) {
        new_array[j] = array_1[i]; 
        j++;
    }

    for (size_t i = 0; i < size_2; i++) {
        new_array[j] = array_2[i]; 
        j++;
    }

    return new_array;
}

// Read the number of elements, allocate the array and read its elements
// Condition: number of elements > 0
// Pre-Condition: size_p != NULL
// Return NULL if memory allocation fails
// Set *size_p to ZERO if memory allocation fails
double* ReadArray(size_t* size_p) { 
    assert(size_p != NULL);

    size_t n;
    printf("Enter the number of elements: ");
    scanf("%lu", &n);

    double* array = malloc( n * sizeof(double));
    if (array == NULL) {
        *size_p = 0;
        return NULL;
    }

    for (size_t i = 0; i < n; i++) {
        printf("Enter the element: ");
        scanf("%lf", &array[i]);
    }

    DisplayArray(array, n);
    *size_p = n;
    return array;
}

// Test example: Array = [ 1.00, 2.00, 3.00 ]
// Array = [ 4.00, 5.00, 6.00, 7.00 ]
// Array = [ 1.00, 2.00, 3.00, 4.00, 5.00, 6.00, 7.00 ]

int main(void) {
    double arr1[] = {1.00, 2.00, 3.00};
    DisplayArray(arr1, 3);

    double arr2[] = {4.00, 5.00, 6.00, 7.00};
    DisplayArray(arr2, 4);

    double* arr3 = Append(arr1, 3, arr2, 4);
    DisplayArray(arr3, 7);

    size_t n4;
    double* arr4 = ReadArray(&n4);
    DisplayArray(arr4, n4);
    return 0;
}