#include <stdio.h>

int f(int x){

	int i,j,r;
	r=0;
	
	for( i=0 ; i<=x ; i++ )
		for( j=0 ; j<=i ; j++)
			r+= i*j;
	
	return r;
}

int main (){

	printf("f(2): %i\n", f(2));
	printf("f(3): %i\n", f(3));

	return 0;
}
