#include <stdio.h>

int main(){

int num =20;
int* pNum;

int array[10] = {0,1,2,3,4,5,6,7,8,9};
int *pArray;
int* p2Array;

printf("Valor de num: %i \n", num);
printf("Endereço de num: %p \n\n", &num);

printf("pNum = &num...\n");
pNum=&num;

printf("Endereço de pNum: %p\n", pNum);
printf("Conteúdo de pNUm: %i\n", *pNum);

printf("Index 0 do array: %i\n", array[0]);
printf("Index 1 do array: %i\n", array[1]);
printf("Endereço do array: %p\n\n", array);

pArray=&array[1];

printf("pArray=array[1]...\n");
printf("Endereço de pArray: %p\n", pArray);
printf("Conteúdo de pArray: %i\n", *pArray);
printf("Endereço de (pArray+1): %p\n", (pArray+1));
printf("Conteúdo de (pArray+1): %i\n\n", *(pArray+1));

printf("Vamos aceder fora do array...\n");
printf("p2Array=&array[9]...\n");

p2Array=&array[9];

printf("Endereço de p2Array: %p \n", p2Array);
printf("Conteúdo de p2Array: %i \n", *p2Array);
printf("Endereço de (p2Array+1): %p \n", (p2Array+1));
printf("Conteúdo de (p2Array+1): %i \n", *(p2Array+1));




return 0;
}
