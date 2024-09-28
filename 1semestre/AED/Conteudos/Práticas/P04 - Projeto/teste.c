#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int n = 16;
    printf("%ld\n",n*sizeof(int));
    int * dists = malloc(n*sizeof(int));
    memset(dists, 0, n*sizeof(int));
    for(int i = 0; i < n; i++)
        dists[i]++;

    dists = realloc(dists, 32*sizeof(int));
    memset(&dists[16],0, (32-16)*sizeof(int));
        for(int i = 0; i < 32; i++)
            printf("%d  -> %d\n",i,dists[i]);
    free(dists);
    return 0;
}
