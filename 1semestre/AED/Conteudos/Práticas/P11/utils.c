#include "utils.h"
#include <stdlib.h>
#include <string.h>

int factorize(int n,int *factors[]){
	int buf[n];
	int i=0;
	for(int f=n;f>0;f--){
		if(n%f==0){
			buf[i++]=f;
		}
	}
	*factors=(int *) malloc(sizeof(int)*i);
	memcpy(*factors,buf,sizeof(int)*i);
	return i;
}