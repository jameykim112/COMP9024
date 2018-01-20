// Graph ADT
// Adjacency Matrix Representation ... COMP9024 17s2
#include "Graph.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Graph structure
typedef struct GraphRep {
   int  **edges;   // adjacency matrix
   int    nV;      // #vertices
   int    nE;      // #edges
} GraphRep;

// V represents the number of nodes
Graph newGraph(int V) {
   assert(V >= 0);
   int i;

   // Memory of g
   Graph g = malloc(sizeof(GraphRep));
   assert(g != NULL);
   g->nV = V;
   g->nE = 0;

   // allocate memory for each row
   g->edges = malloc(V * sizeof(int *));
   assert(g->edges != NULL);
   // allocate memory for each column and initialise with 0
   for (i = 0; i < V; i++) {
      g->edges[i] = calloc(V, sizeof(int)); //V = no. elements, sizeof(int) is type
      assert(g->edges[i] != NULL);
   }

   return g;
}

// check if vertex is valid in a graph
bool validV(Graph g, Vertex v) {
   return (g != NULL && v >= 0 && v < g->nV);
}

void insertEdge(Graph g, Edge e) {
   assert(g != NULL && validV(g,e.v) && validV(g,e.w));

   if (!g->edges[e.v][e.w]) {  // edge e not in graph
      g->edges[e.v][e.w] = 1;
      //g->edges[e.w][e.v] = 1;
      g->nE++;
   }
}

void removeEdge(Graph g, Edge e) {
   assert(g != NULL && validV(g,e.v) && validV(g,e.w));

   if (g->edges[e.v][e.w]) {   // edge e in graph
      g->edges[e.v][e.w] = 0;
      g->edges[e.w][e.v] = 0;
      g->nE--;
   }
}

bool adjacent(Graph g, Vertex v, Vertex w) {
   assert(g != NULL && validV(g,v) && validV(g,w));

   return (g->edges[v][w] != 0);
}

void showGraph(Graph g, char **word_set) {
    printf("\n");
    assert(g != NULL);
    int i, j;

    for (i = 0; i < g->nV; i++) {
      printf("%s: ", word_set[i]);
      for (j = i+1; j < g->nV; j++) {
        if (g->edges[i][j]) {
          printf("%s ", word_set[j]);
        }
      }
      printf("\n");
    }
    printf("\n");
}

void freeGraph(Graph g, int nV, char **word_set) {
   assert(g != NULL);

   int i;
   for (i = 0; i < g->nV; i++)
      free(g->edges[i]);
      free(g->edges);
      free(g);

    int j;
    for (j = 0; j < nV; j++) {
      free(word_set[j]);
    }
}
