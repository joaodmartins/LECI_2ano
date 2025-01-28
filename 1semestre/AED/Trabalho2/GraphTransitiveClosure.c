//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphTransitiveClosure - Transitive Closure of a directed graph
//

// Student Name :
// Student Number :
// Student Name :
// Student Number :

/*** COMPLETE THE GraphComputeTransitiveClosure FUNCTION ***/

#include "GraphTransitiveClosure.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphBellmanFordAlg.h"
#include "instrumentation.h"

// Compute the transitive closure of a directed graph
// Return the computed transitive closure as a directed graph
// Use the Bellman-Ford algorithm
Graph* GraphComputeTransitiveClosure(Graph* g) {
  assert(g != NULL);
  assert(GraphIsDigraph(g));
  assert(GraphIsWeighted(g) == 0);

  // Obter número de vértices
  unsigned int numVertices = GraphGetNumVertices(g);

  // Criar o grafo de fecho transitivo
  Graph* closureGraph = GraphCreate(numVertices, 1, 0);  // Digrafo não ponderado

  for (unsigned int v = 0; v < numVertices; v++) {
    // Executar Bellman-Ford a partir do vértice v
    GraphBellmanFordAlg* bfAlg = GraphBellmanFordAlgExecute(g, v);

    // Verificar os vértices alcançáveis a partir de v
    for (unsigned int w = 0; w < numVertices; w++) {
      if (GraphBellmanFordAlgReached(bfAlg, w)) {
        // Adicionar aresta no fecho transitivo
        GraphAddEdge(closureGraph, v, w);
      }
    }

    // Destruir a instância de Bellman-Ford
    GraphBellmanFordAlgDestroy(&bfAlg);
  }

  return closureGraph;
}
