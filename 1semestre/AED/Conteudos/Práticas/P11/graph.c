#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "utils.h"

#define TRUE 1
#define FALSE 0

vertex *createVertex(int x, int y){
	vertex *v = (vertex *) malloc(sizeof(vertex));
	v->x = x;
	v->y = y;

	return v;
}

void sprintVertex(char *str, vertex *v){
	sprintf(str,"(%d,%d)",v->x,v->y);
}

void freeVertex(vertex *v){
	free(v);
}

int mdcVertex(vertex *v){
	int *fX;
	int *fY;

	int nfX = factorize(v->x, &fX);
	int nfY = factorize(v->y, &fY);

	for(int i = 0 ; i < nfX ; i++){
		for(int j = 0 ; j < nfY ; j++){
			if(fX[i] == fY[j]){
				return fX[i];
			}
			//This is very much optimizable
		}
	}

	return 0; //we never reach this point because 1 is always an MDC
}

int isConnected(vertex *v1, vertex *v2){
	if(v1 == NULL || v2 == NULL){
		return FALSE;
	}
	if(mdcVertex(v1) == mdcVertex(v2)){
		return TRUE;
	}
	return FALSE;
}

vertex *createConnectedVertex(vertex *v){
	vertex *nv = NULL;

	while(!isConnected(v,nv)){
		if(nv !=NULL)
			freeVertex(nv);

		nv = createVertex(random()%30, random()%30);
	}
	return nv;
}

vertex **createConnectedGraph(vertex *seed, int nVertices){
	vertex **g;
	g = (vertex **) malloc(sizeof(vertex *) * nVertices);	//Graph -> Array of vertices

	g[0] = seed;

	for(int i = 1 ; i < nVertices ; i++){
		g[i] = createConnectedVertex(g[i-1]);
	}

	return g;
}


