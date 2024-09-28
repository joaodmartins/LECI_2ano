#ifndef GRAPH_H_
#define GRAPH_H_

typedef struct vertex {
	int x;
	int y;
} vertex;

vertex *createVertex(int x,int y);	//Constructor
void freeVertex(vertex *);	//Destructor
void sprintVertex(char *, vertex *); //Print vertex
int mdcVertex(vertex *);	//Return minimum common divisor of vertex
vertex *createConnectedVertex(vertex *v);	//Returns a vertex that is for sure connected to the given vertex
int isConnected(vertex *v1, vertex *v2);	//Checks if 2 vertices are connected
vertex **createConnectedGraph(vertex *seed, int nVertices); //Returns an array which contains of nVertices connected vertices

#endif