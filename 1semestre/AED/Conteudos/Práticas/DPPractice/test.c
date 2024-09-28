#include <stdio.h>
#include "cities.h"
#include "elapsed_time.h"

#define INT_MAX 999999
//#define MIN(a,b) (((a)<(b))?(a):(b))

int n = 8;
int knownPaths[18][1<<18];
int minPath[18][1<<18];


/*int dist[10][10] ={
	{0 , 100, 100, 25},
	{100,  100, 10, 100},
	{10, 100,  0, 100},
	{100, 34, 100,  0},
};*/

//Pos -> From which city TSP is departing
int getLowestPath(int mask,int pos){	
	if(mask == ((1<<n) -1)){	//(1<<n) -1 -> Mask thats all 1's
		//return dist[pos][0]; //Get distance from last city visited back to A
		return cities[pos].distance[0];
	}

	//Check if we already have that distance calculated
			//printf("%d",path[pos][mask]);

	if(knownPaths[pos][mask] != -1){
		return knownPaths[pos][mask];
	}

	int ans = INT_MAX;
	//int ans = 0;

	for(int city = 0 ; city < n ; city++){
		if((mask & (1<<city)) == 0){	//Check if city hasnt been visited
			int newAns = cities[pos].distance[city]+ getLowestPath(mask|(1<<city),city);

			//if(ans < newAns){ if we want the max path
			if(ans > newAns){ //if we want the min path
				ans = newAns;
				minPath[pos][mask] = city;
			}
			//ans = MIN(ans,newAns);
		}
	}
	return knownPaths[pos][mask] = ans;
}

int main(){
	/*path[0] = 0;
	pathIndex++;*/

	int n_mec, special;
	double time;

	n_mec = 0; // CHANGE THIS!
	special = 0;   // CHANGE TO 1 or 0
	init_cities_data(n_mec, special);


	(void)elapsed_time();
	for(n = 3 ; n < 19 ; n ++){
		for(int i = 0; i<n ; i++){
			for(int j = 0 ; j<(1<<n) ; j++){
				knownPaths[i][j] = -1;
			}
		}
		printf("%d\n", getLowestPath(1,0));

		//Print minimum path
		int path[n];
		int pathIndex = 0;
		int curNode = 0;
		int curMask = 1;

		do{
			path[pathIndex] = curNode;
			pathIndex++;
			curNode = minPath[curNode][curMask];
			curMask = curMask | (1 << curNode);
		}while(curNode != 0);

		for(int i = 0; i < n ; i++){
			printf("%d\n", path[i]);
		}

		printf("\n");
	}
	time = elapsed_time();
	printf("%f\n",time);
	return 0;

}
