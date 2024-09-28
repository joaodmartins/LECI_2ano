//
// Tomás Oliveira e Silva, AED, October 2021
//
// program to print a table of the squares and square roots of some integers
//
// on GNU/Linux, run the command
//   man 3 printf
// to see the manual page of the printf function
//

#include <math.h>
#include <stdio.h>

void do_it(int N)
{
  int i;

  printf(" n n*n      sqrt(n)\n");
  printf("-- --- -----------------\n");
  for(i = 1;i <= N;i++)
    printf("%2d %3d %17.15f\n",i,i * i,sqrt((double)i));
}

void doItAgain(int N){
	FILE *fp;
	fp = fopen ("table.txt","w");

	fprintf(fp, "\n n  cos(n)   sin(n)\n");
 	fprintf(fp, "-- -------- --------\n");
 	for(int i = 0; i<= N ; i++){
 		fprintf(fp, "%2d %8.5f %8.5f\n",i,cos(i*(M_PI/180.0)),sin(i*(M_PI/180.0)));
 	}

 	fclose(fp);
}

int main(void)
{
  do_it(10);
  doItAgain(90);
  return 0;
}
