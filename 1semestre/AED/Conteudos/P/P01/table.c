//
// Tomás Oliveira e Silva, AED, September 2014, September 2017
//
// program to print a table of the squares and square roots of some integers
//
// on GNU/Linux, run the command
//   man 3 printf
// to see how the manual page of the printf function
//

#include <math.h>
#include <stdio.h>

void do_it(void)
{
  int i;
  long t;

  printf(" n sin(n)      cos(n)    10^\n");
  printf("-- ------ ------ -------------------\n");
  t=1;
  for(i = 1;i <= 90;i++)
  {
    printf("%2d %6.4f %6.4f %20ld \n",i,sin((double)i/180.0 *M_PI) ,cos((double)i/180.0 *M_PI), t);
    t*=10;
  }
}

int main(void)
{
  do_it();
  return 0;
}
