//
// Tomás Oliveira e Silva, AED, September 2014, September 2015
//
// the functions for the first exercise of class P.03
// (for a given positive value of n, find a formula for the return value of each function)
//

#include <stdio.h>
#include "elapsed_time.h"

int f1(int n)
{
  int i,r=0;

  for(i = 1;i <= n;i++)
    r += 1;
  return r;
}

int f2(int n)
{
  int i,j,r=0;

  for(i = 1;i <= n;i++)
    for(j = 1;j <= i;j++)
      r += 1;
  return r;
}

int f3(int n)
{
  int i,j,r=0;

  for(i = 1;i <= n;i++)
    for(j = 1;j <= n;j++)
      r += 1;
  return r;
}

int f4(int n)
{
  int i,r=0;

  for(i = 1;i <= n;i++)
    r += i;
  return r;
}

int f5(int n)
{
  int i,j,r=0;

  for(i = 1;i <= n;i++)
    for(j = i;j <= n;j++)
      r += 1;
  return r;
}

int f6(int n)
{
  int i,j,r=0;

  for(i = 1;i <= n;i++)
    for(j = 1;j <= i;j++)
      r += j;
  return r;
}

int main(void)
{
  double dt1,dt2,dt3,dt4,dt5,dt6 = 0;
  FILE *fp = fopen("functions.csv","w");
  fprintf(fp,"n;f1;f2;f3;f4;f5;f6\n");

  for(int n = 1; n<=100000; n+=10000){
    (void)elapsed_time();
    f1(n);
    dt1 = elapsed_time();

    (void)elapsed_time();
    f2(n);
    dt2 = elapsed_time();

    (void)elapsed_time();
    f3(n);
    dt3 = elapsed_time();

    (void)elapsed_time();
    f4(n);
    dt4 = elapsed_time();

    (void)elapsed_time();
    f5(n);
    dt5 = elapsed_time();

    (void)elapsed_time();
    f6(n);
    dt6 = elapsed_time();

    fprintf(fp,"%d;%12.9f;%12.9f;%12.9f;%12.9f;%12.9f;%12.9f\n",n,dt1,dt2,dt3,dt4,dt5,dt6);
    if(n==1){
      n = 0;
    }
  }

  fclose(fp);

}
