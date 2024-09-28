#include <stdio.h>

int main (){
	
	int a[100];

	for( int i=0 ; i<100 ; i++)
		a[i]=i;

	int *pa=&a[-10];
	int *pb=pa+23;
	printf("%i\n", *pb);

	for (int i = 20; i <= 40 ; i++){
		a[i] = pb[i];
	}
	for (int i =0 ; i<100; i++)
		printf("a[%i]: %i\n",i, a[i]);

	return 0;
}
