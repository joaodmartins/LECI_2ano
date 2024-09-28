//
// Vasco Ramos; 88931
// Diogo Silva; 89348
// ...
//
// AED, 2018/2019
//
// solution of the traveling salesman problem
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <assert.h>

#include "cities.h"
#include "../P01/elapsed_time.h"

#define INT_MAX 999999


//
// record best solutions
//

static int min_length, max_length, distance;
static int min_tour[max_n_cities + 1], max_tour[max_n_cities + 1];
static long n_tours;
int *dados = NULL;
int dados_size;

//DP
int knownPaths[18][1<<18];
int pathArray[18][1<<18];

//
// first solution (brute force, distance computed at the end, compute best and worst tours)
//

void max_min(int distance, int n, int *a)
{
  int i;
  if (distance < min_length)
  {
    min_length = distance;
    for (i = 0; i <= n; i++)
      min_tour[i] = a[i];
  }
  if (distance > max_length)
  {
    max_length = distance;
    for (i = 0; i <= n; i++)
      max_tour[i] = a[i];
  }
}

//PARTE 1
void tsp_v1(int n, int m, int *a)
{
  int i, t;
  distance = 0;
  if (m < n - 1)
    for (i = m; i < n; i++)
    {
      t = a[m];
      a[m] = a[i];
      a[i] = t;
      tsp_v1(n, m + 1, a);
      t = a[m];
      a[m] = a[i];
      a[i] = t;
    }
  else
  { // visit permutation
    n_tours++;
    // modify the following code to do your stuff
    a[n] = a[0]; // a ultima cidade tem de ser a mesma que a primeira para termos a dist entre a penultima e a primeira
    for (i = 0; i < n; i++)
      distance += cities[a[i]].distance[a[i + 1]];
    // como as dists ja estao definidas é só ir buscar os seus valores e somar
    if (n == 12 || n == 15)
    {
      if (dados_size <= distance)
      {
      int tmp = dados_size;
      dados_size += dados_size; 
      dados = realloc(dados, dados_size * sizeof(int));
      for (int i = tmp; i < dados_size; i++)
        dados[i] = 0;
      }
      dados[distance]++;
    }
  }
  max_min(distance, n, a);
}

//
//PROGRAMACAO DINAMICA
//

int getDistanceDP(int n,int mask,int pos,int minOrMax){  
  if(mask == ((1<<n) -1)){  //(1<<n) -1 -> Mask thats all 1's

    //return dist[pos][0]; //Get distance from last city visited back to A
    return cities[pos].distance[0];
  }

  //Check if we already have that distance calculated
  if(knownPaths[pos][mask] != -1){
    return knownPaths[pos][mask];
  }

  int ans = INT_MAX;
  if(minOrMax == 1){
    ans = 0;    
  }

  for(int city = 0 ; city < n ; city++){
    if((mask & (1<<city)) == 0){  //Check if city hasnt been visited
      n_tours++;
      int newAns = cities[pos].distance[city]+ getDistanceDP(n,mask|(1<<city),city,minOrMax);

      if(minOrMax == 1){ //if we want the max path
        if(ans < newAns){
          ans = newAns;
          pathArray[pos][mask] = city;
        }      
        continue;
      }

      if(ans > newAns){ //if we want the min path
        ans = newAns;
        pathArray[pos][mask] = city;
      }
      //ans = MIN(ans,newAns);
    }
  }
  return knownPaths[pos][mask] = ans;
}

void tspV2(int n){
  int pathIndex;
  int curNode;
  int curMask;

  //Initialize minKnownPaths Array
  for(int i = 0; i<n ; i++){
    for(int j = 0 ; j<(1<<n) ; j++){
      knownPaths[i][j] = -1;
    }
  }

  //Use function to get minLength
  min_length = getDistanceDP(n,1,0,0);

  pathIndex = 0;
  curNode = 0;
  curMask = 1;

  //Add the path to the min_Tour path
  do{
      min_tour[pathIndex] = curNode;
      pathIndex++;
      curNode = pathArray[curNode][curMask];
      curMask = curMask | (1 << curNode);
  }while(curNode != 0);


  //Initialize maxKnownPaths Array
  for(int i = 0; i<n ; i++){
    for(int j = 0 ; j<(1<<n) ; j++){
      knownPaths[i][j] = -1;
    }
  }

  //Use function to get maxLength
  max_length = getDistanceDP(n,1,0,1);

  pathIndex = 0;
  curNode = 0;
  curMask = 1;

  //Add the path to the max_Tour path
  do{
      max_tour[pathIndex] = curNode;
      pathIndex++;
      curNode = pathArray[curNode][curMask];
      curMask = curMask | (1 << curNode);
  }while(curNode != 0);


}




void rand_perm(int n, int a[])
{
  int i, j, k;
  distance = 0;
  for (i = 0; i < n; i++)
    a[i] = i;
  for (i = n - 1; i > 0; i--)
  {
    j = (int)floor((double)(i + 1) * (double)rand() / (1.0 + (double)RAND_MAX)); // range 0..i
    assert(j >= 0 && j <= i);
    k = a[i];
    a[i] = a[j];
    a[j] = k;
  }
  n_tours++;
  // modify the following code to do your stuff
  a[n] = a[0]; // a ultima cidade tem de ser a mesma que a primeira para termos a dist entre a penultima e a primeira
  for (i = 0; i < n; i++)
    distance += cities[a[i]].distance[a[i + 1]];
  // como as dists ja estao definidas é só ir buscar os seus valores e somar
  if ( n == 12 || n == 15 || n == 18 )
  {
    if (dados_size <= distance)
    {
      int tmp = dados_size;
      dados_size += dados_size;
      dados = realloc(dados, dados_size * sizeof(int));
      for (int i = tmp; i < dados_size; i++)
        dados[i] = 0;
    }
    dados[distance]++;
  }
  max_min(distance, n, a);
}

//
// main program
//

int main(int argc, char **argv)
{
  int n_mec, special, n, i;
  int a[max_n_cities + 1]; // array onde vao estar guardadas as cidades
  char file_name[32], name[32], time[64];
  double dt1;

  n_mec = 89348; // CHANGE THIS!
  special = 0;   // CHANGE TO 1 or 0
  init_cities_data(n_mec, special);
  printf("data for init_cities_data(%d,%d)\n", n_mec, special);
  fflush(stdout);
#if 0
  print_distances();
#endif
#if 1
  for (n = 3; n <= 15; n++)
  {
    //
    // try tsp_v1
    //
    dt1 = -1.0;
    if (n <= 16)
    {
      dados_size = 3000;
      dados = malloc(dados_size * sizeof(int));
      memset(dados, 0, dados_size * sizeof(int));
      (void)elapsed_time();
      for (i = 0; i < n; i++)
        a[i] = i;
      min_length = 1000000000;
      max_length = 0;
      n_tours = 0l;
      tsp_v1(n, 1, a); // no need to change the starting city, as we are making a tour
      dt1 = elapsed_time();
      if (n == 12 || n == 15)
      {
        sprintf(name, "dados_%02d_%d_%d.txt", n,n_mec,special);
        FILE *fd = fopen(name, "wb");
        for (int i = 0; i < dados_size; i++)
          fprintf(fd, "%d %d\n", i, dados[i]);
        fclose(fd);
      }

      free(dados);
      printf("tsp_v1() finished in %4fs (%ld tours generated)\n", dt1, n_tours);
      printf("  min %5d [", min_length);
      for (i = 0; i < n; i++)
        printf("%2d%s", min_tour[i], (i == n - 1) ? "]\n" : ",");
      printf("  max %5d [", max_length);
      for (i = 0; i < n; i++)
        printf("%2d%s", max_tour[i], (i == n - 1) ? "]\n" : ",");
      fflush(stdout);
      if (argc == 2 && strcmp(argv[1], "-f") == 0)
      {
        min_tour[n] = -1;
        sprintf(file_name, "min_%02d_%d_%d.svg", n,n_mec,special);
        make_map(file_name, min_tour);
        max_tour[n] = -1;
        sprintf(file_name, "max_%02d_%d_%d.svg", n,n_mec,special);
        make_map(file_name, max_tour);
      }

      sprintf(time, "%s;%d;%d;%d;%f\n", "BF", n,n_mec,special,dt1);
      FILE *fd = fopen("Tempos.txt", "a");
      fprintf(fd, "%s",time);
      fclose(fd);
    }
  }
#endif

//DYNAMIC PROGRAMMING
#if 1
  for (n = 3; n <= 18; n++)
  {
    //
    // try tspV2
    //
    dt1 = -1.0;
      
    (void)elapsed_time();

    n_tours = 0l;

    tspV2(n);

    dt1 = elapsed_time();

    printf("tspV2() finished in %4fs (%ld tours generated)\n", dt1, n_tours);
    printf("  min %5d [", min_length);
    for (i = 0; i < n; i++)
      printf("%2d%s", min_tour[i], (i == n - 1) ? "]\n" : ",");
    
    printf("  max %5d [", max_length);
    for (i = 0; i < n; i++)
      printf("%2d%s", max_tour[i], (i == n - 1) ? "]\n" : ",");
    
    fflush(stdout);
    if (argc == 2 && strcmp(argv[1], "-f") == 0)
    {
      min_tour[n] = -1;
      sprintf(file_name, "min_%02d_%d_%d.svg", n,n_mec,special);
      make_map(file_name, min_tour);
      max_tour[n] = -1;
      sprintf(file_name, "max_%02d_%d_%d.svg", n,n_mec,special);
      make_map(file_name, max_tour);
    }
    
    sprintf(time, "%s;%d;%d;%d;%f\n", "DP", n,n_mec,special,dt1);
    FILE *fd = fopen("Tempos.txt", "a");
    fprintf(fd, "%s",time);
    fclose(fd);
  }
#endif

#if 1
  for(n = 12; n < 19; n+=3)
  {
    dados_size = 3000;
    dados = malloc(dados_size * sizeof(int));
    memset(dados, 0, dados_size * sizeof(int));
    (void)elapsed_time();
    min_length = 1000000000;
    max_length = 0;
    n_tours = 0l;
    for (int i = 0; i < 1000000000; i++)
      rand_perm(n, a);
    dt1 = elapsed_time();
    if (n <= 18)
    {
      sprintf(name, "dados_rand_%02d_%d_%d.txt", n,n_mec,special);
      FILE *fd = fopen(name, "wb");
      for (int i = 0; i < dados_size; i++)
        fprintf(fd, "%d %d\n", i, dados[i]);
      fclose(fd);
    }
    free(dados);
    printf("rand_perm() finished in %4fs (%ld tours generated)\n", dt1, n_tours);
    printf("  min %5d [", min_length);
    for (i = 0; i < n; i++)
      printf("%2d%s", min_tour[i], (i == n - 1) ? "]\n" : ",");
    printf("  max %5d [", max_length);
    for (i = 0; i < n; i++)
      printf("%2d%s", max_tour[i], (i == n - 1) ? "]\n" : ",");
    fflush(stdout);
    if (argc == 2 && strcmp(argv[1], "-f") == 0)
    {
      min_tour[n] = -1;
      sprintf(file_name, "min_random_%02d_%d_%d.svg", n,n_mec,special);
      make_map(file_name, min_tour);
      max_tour[n] = -1;
      sprintf(file_name, "max_random_%02d_%d_%d.svg", n,n_mec,special);
      make_map(file_name, max_tour);
    }

    sprintf(time, "%s;%d;%d;%d;%f\n", "RANDOM", n,n_mec,special,dt1);
    FILE *fd = fopen("Tempos.txt", "a");
    fprintf(fd, "%s",time);
    fclose(fd);
  }
#endif
  return 0;
}
