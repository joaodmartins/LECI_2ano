#include <stdio.h>

void swap(int x , int y){

	int z=x;
	x=y;
	y=z;
}

int main(){

	int i=3;
	int j=4;
	swap(i,j);
	
	printf("Valor de i: %i\n", i);
	printf("Valor de j: %i\n",j);

	return i+j;
}

