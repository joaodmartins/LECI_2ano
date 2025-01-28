//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphBellmanFord - Bellman-Ford Algorithm
//

// Student Name :
// Student Number :
// Student Name :
// Student Number :

/*** COMPLETE THE GraphBellmanFordAlgExecute FUNCTION ***/

#include "GraphBellmanFordAlg.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "IntegersStack.h"
#include "instrumentation.h"

struct _GraphBellmanFordAlg {
  unsigned int* marked;  // To mark vertices when reached for the first time
  int* distance;  // The number of edges on the path from the start vertex
                  // distance[i]=-1, if no path found from the start vertex to i
  int* predecessor;  // The predecessor vertex in the shortest path
                     // predecessor[i]=-1, if no predecessor exists
  Graph* graph;
  unsigned int startVertex;  // The root of the shortest-paths tree
};

GraphBellmanFordAlg* GraphBellmanFordAlgExecute(Graph* g,
                                                unsigned int startVertex) {
  assert(g != NULL);
  assert(startVertex < GraphGetNumVertices(g));
  assert(GraphIsWeighted(g) == 0);

  GraphBellmanFordAlg* result =
      (GraphBellmanFordAlg*)malloc(sizeof(struct _GraphBellmanFordAlg));
  assert(result != NULL);

  // Given graph and start vertex for the shortest-paths
  result->graph = g;
  result->startVertex = startVertex;

  unsigned int numVertices = GraphGetNumVertices(g);

  //
  // TO BE COMPLETED !!
  //
  // CREATE AND INITIALIZE
  // result->marked
  // result->distance
  // result->predecessor
  //
  // Mark all vertices as not yet visited, i.e., ZERO
  
  // No vertex has (yet) a (valid) predecessor

  // No vertex has (yet) a (valid) distance to the start vertex
  result->marked = (unsigned int*)calloc(numVertices, sizeof(int) );
  result->predecessor = (int*)malloc(numVertices * sizeof(int));
  result->distance = (int*)malloc(sizeof(int) * numVertices);

  // initialize struct variables
  for (unsigned int i = 0; i < GraphGetNumVertices(g); i++){
    result->distance[i] = __INT_MAX__;
    result->predecessor[i] = -1;
  }
  //distance from starter vertex to itself is 0 
  result->distance[startVertex] = 0;
  
  //variable to monitor if the algorithm has changed after an iteration or not
  unsigned int change = 1;

  //repeat |V|-1 times: 
  for (unsigned int i = 0; i < GraphGetNumVertices(g)-1; i++){

    //if the algorithm does not change any path in an iteration, then it will also not change
    //anything in the remaining iterations, therefore we can optimize the code by adding a
    //variable that will stop as soon as the shortest paths were found.
    if (change == 0)break;
    change = 0;

    //iterate over every edge:

    //for every vertex v  
    for (unsigned int v = 0; v < GraphGetNumVertices(g); v++){

      //get the adjacent vertices of v
      unsigned* adjacent = GraphGetAdjacentsTo(g, v);

      //get the weight for each vertex adjacent of v ///// edge(v, adjacent[w]) has weight[w]
      double* weight = GraphGetDistancesToAdjacents(g, v);
      
      //for each adjacent vertex of v
      for (unsigned int j = 1; j <= adjacent[0]; j++){
        //get weight for that edge
        unsigned int w = adjacent[j];

        //if the distance until v + weight of this edge is < distance until w, then 
        if (result->distance[v] + weight[j] < result->distance[w]){

          //v has a shortest path, make it so the shortest path goes through v to get to w
          //give distance
          result->distance[w] = result->distance[v] + weight[j];

          //give predecessor
          result->predecessor[w] = v;

          //mark as visited
          result->marked[w] = 1;

          change = 1;
          }
        }
        free(adjacent);
        free(weight);
      }
    }

    //check for negative cycles and unmarked vertices
    //iterate through all edges, like before
    for (unsigned int v = 0; v < GraphGetNumVertices(g); v++){
      unsigned* adjacent = GraphGetAdjacentsTo(g, v);
      double* weight = GraphGetDistancesToAdjacents(g, v);
      
    if(change == 1){

      for (int j = 1; j <= weight[0]; j++){
        unsigned int w = adjacent[j];
        
        //if any distance is updated this time, it means it required |V|  
        //iterations to get the shortest path, therefore there is a negative cycle.
        if (result->distance[v] + weight[j] < result->distance[w]){
          printf("theres a negative cycle");
          result->distance[startVertex] = -1;
        }
      }
      if (result->distance[v] == __INT_MAX__){
              result->distance[v] = -1;
            }
    }   
    free(weight);
    free(adjacent);
  }
  return result;
}

void GraphBellmanFordAlgDestroy(GraphBellmanFordAlg** p) {
  assert(*p != NULL);

  GraphBellmanFordAlg* aux = *p;

  free(aux->marked);
  free(aux->predecessor);
  free(aux->distance);

  free(*p);
  *p = NULL;
}

// Getting the paths information

int GraphBellmanFordAlgReached(const GraphBellmanFordAlg* p, unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  return p->marked[v];
}

int GraphBellmanFordAlgDistance(const GraphBellmanFordAlg* p, unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  return p->distance[v];
}
Stack* GraphBellmanFordAlgPathTo(const GraphBellmanFordAlg* p, unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  Stack* s = StackCreate(GraphGetNumVertices(p->graph));

  if (p->marked[v] == 0) {
    return s;
  }

  // Store the path
  for (unsigned int current = v; current != p->startVertex;
       current = p->predecessor[current]) {
    StackPush(s, current);
  }

  StackPush(s, p->startVertex);

  return s;
}

// DISPLAYING on the console

void GraphBellmanFordAlgShowPath(const GraphBellmanFordAlg* p, unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  Stack* s = GraphBellmanFordAlgPathTo(p, v);

  while (StackIsEmpty(s) == 0) {
    printf("%d ", StackPop(s));
  }

  StackDestroy(&s);
}

// Display the Shortest-Paths Tree in DOT format
void GraphBellmanFordAlgDisplayDOT(const GraphBellmanFordAlg* p) {
  assert(p != NULL);

  Graph* original_graph = p->graph;
  unsigned int num_vertices = GraphGetNumVertices(original_graph);

  // The paths tree is a digraph, with no edge weights
  Graph* paths_tree = GraphCreate(num_vertices, 1, 0);

  // Use the predecessors array to add the tree edges
  for (unsigned int w = 0; w < num_vertices; w++) {
    // Vertex w has a predecessor vertex v?
    int v = p->predecessor[w];
    if (v != -1) {
      GraphAddEdge(paths_tree, (unsigned int)v, w);
    }
  }

  // Display the tree in the DOT format
  GraphDisplayDOT(paths_tree);

  // Housekeeping
  GraphDestroy(&paths_tree);
}
