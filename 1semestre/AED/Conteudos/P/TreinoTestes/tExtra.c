#include <stdio.h>
#include <stdlib.h>

int main(){

	int n=4;
	int *a[];
// the  number of rows and of columns of the matrix
// the matrix

	int i,k,s,*p; // auxiliary variables
	// the total number of elements of the matrix
	// (missing value to be computed by the student)

	s =n*n ;

	// allocate memory for the array of pointers
	a = (int *[])malloc((size_t)n * sizeof(int *));
	// the memory for ALL elements
	p = (int *)malloc((size_t)s * sizeof(int));

	assert(a != NULL && p != NULL);

	for(i = 0;i < n;i++){
	
	// the number of valid elements on the i-th line
	k = i + 1;
	// the pointer for the i-th line; this line uses p[0], p[1], ..., p[k-1];
	// the remaining elements of this line will never be used by a correct program
	a[i] = p;
	// advance p
	p += k;
	}
}
