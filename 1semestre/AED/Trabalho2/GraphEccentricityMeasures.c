//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphEccentricityMeasures
//

// Student Name :
// Student Number :
// Student Name :
// Student Number :

/*** COMPLETE THE GraphEccentricityMeasuresCompute FUNCTION ***/
/*** COMPLETE THE GraphGetCentralVertices FUNCTION ***/
/*** COMPLETE THE GraphEccentricityMeasuresPrint FUNCTION ***/

#include "GraphEccentricityMeasures.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphAllPairsShortestDistances.h"

struct _GraphEccentricityMeasures {
  unsigned int*
      centralVertices;  // centralVertices[0] = number of central vertices
                        // array size is (number of central vertices + 1)
  int* eccentricity;    // the eccentricity value of each vertex
  Graph* graph;         // the graph
  int graphRadius;      // the graph radius
  int graphDiameter;    // the graph diameter
};

// Allocate memory
// Compute the vertex eccentricity values
// Compute graph radius and graph diameter
// Compute the set of central vertices
GraphEccentricityMeasures* GraphEccentricityMeasuresCompute(Graph* g) {
  assert(g != NULL);

  // Alocar memória para os resultados
  GraphEccentricityMeasures* result = malloc(sizeof(GraphEccentricityMeasures));
  result->graph = g;

  unsigned int numVertices = GraphGetNumVertices(g);
  
  // Calcular todas as distâncias de pares de vértices
  GraphAllPairsShortestDistances* allPairs = GraphAllPairsShortestDistancesExecute(g);

  result->eccentricity = malloc(numVertices * sizeof(int));
  int maxEccentricity = -1;  // Para calcular o diâmetro
  int minEccentricity = __INT_MAX__;  // Para calcular o raio
  result->graphRadius = -1;
  result->graphDiameter = -1;
  result->centralVertices = malloc((numVertices + 1) * sizeof(unsigned int));  // O primeiro elemento é o número de vértices centrais
  
  unsigned int centralCount = 0;
  
  // Calcular a eccentricidade, o raio e o diâmetro
  for (unsigned int v = 0; v < numVertices; v++) {
    int eccentricity = -1;  // Iniciar com -1 para indicar que o vértice é desconectado
    for (unsigned int w = 0; w < numVertices; w++) {
      int distance = GraphGetDistanceVW(allPairs, v, w);
      if (distance != -1) {  // Ignorar distâncias indefinidas
        if (distance > eccentricity) {
          eccentricity = distance;
        }
      }
    }
    result->eccentricity[v] = eccentricity;
    
    // Atualizar raio e diâmetro
    if (eccentricity != -1) {  // Só considerar distâncias válidas
      if (eccentricity < minEccentricity) {
        minEccentricity = eccentricity;
        result->graphRadius = eccentricity;
      }
      if (eccentricity > maxEccentricity) {
        maxEccentricity = eccentricity;
        result->graphDiameter = eccentricity;
      }
    }
    
    // Encontrar vértices centrais (com eccentricidade igual ao raio)
    if (eccentricity == result->graphRadius) {
      result->centralVertices[centralCount + 1] = v;
      centralCount++;
    }
  }
  
  // Armazenar o número de vértices centrais no primeiro elemento
  result->centralVertices[0] = centralCount;
  
  // Liberar a matriz de distâncias após o uso
  GraphAllPairsShortestDistancesDestroy(&allPairs);

  return result;
}


void GraphEccentricityMeasuresDestroy(GraphEccentricityMeasures** p) {
  assert(*p != NULL);

  GraphEccentricityMeasures* aux = *p;

  free(aux->centralVertices);
  free(aux->eccentricity);

  free(*p);
  *p = NULL;
}

// Getting the computed measures

int GraphGetRadius(const GraphEccentricityMeasures* p) {
  assert(p != NULL);

  return p->graphRadius;
}

int GraphGetDiameter(const GraphEccentricityMeasures* p) {
  assert(p != NULL);

  return p->graphDiameter;
}

int GraphGetVertexEccentricity(const GraphEccentricityMeasures* p,
                               unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));
  assert(p->eccentricity != NULL);

  return p->eccentricity[v];
}

// Getting a copy of the set of central vertices
// centralVertices[0] = number of central vertices in the set
unsigned int* GraphGetCentralVertices(const GraphEccentricityMeasures* p) {
  assert(p != NULL);
  assert(p->centralVertices != NULL);

  // Return the central vertices array
  return p->centralVertices;
}

// Print the graph radius and diameter
// Print the vertex eccentricity values
// Print the set of central vertices
void GraphEccentricityMeasuresPrint(const GraphEccentricityMeasures* p) {
  assert(p != NULL);

  printf("Graph Rardius: %d\n", p->graphRadius);
  printf("Graph Diameter: %d\n", p->graphDiameter);

  printf("Vertex Eccentricities:\n");
  for (unsigned int v = 0; v < GraphGetNumVertices(p->graph); v++) {
    printf("Vertex %u: %d\n", v, p->eccentricity[v]);
  }

  printf("Central Vertices:\n");
  unsigned int centralCount = p->centralVertices[0];
  for (unsigned int i = 1; i <= centralCount; i++) {
    printf("%u ", p->centralVertices[i]);
  }
  printf("\n");
}
