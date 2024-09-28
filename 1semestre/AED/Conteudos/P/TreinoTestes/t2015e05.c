#include <stdio.h>

int f(int n, int m){
	
	int i,j,r;
	r=0;

	for ( i=0 ; i<=n ; i++ ){
		for ( j=i ; j<=m ; j++){
			r+=i;
		}
	}

	printf("Valor de r: %i \n", r);
	return 0;
}

int main(){
	f(5,7);
	return 0;
}
