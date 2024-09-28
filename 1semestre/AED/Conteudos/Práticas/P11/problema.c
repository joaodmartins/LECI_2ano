#include "graph.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	vertex *v1 = createVertex(30,20);

	char buffer[1024];

	//printf("%d\n", mdcVertex(v1));

	vertex **g = createConnectedGraph(v1,4);

	for(int i = 0 ; i < 4 ; i++){
		sprintVertex(buffer,g[i]);
		printf("%s\n",buffer);
	}

	freeVertex(v1);
}