/*** 
* Peter Liang
* xliang41
* 2024 Fall CSE 101 PA3
* Graph.h
* Header file for Graph ADT. 
***/


#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

#define UNDEF -2
#define INF -1
#define NIL 0
#define WHITE 1
#define GRAY 2
#define BLACK 3


typedef struct GraphObj* Graph

// Constructors-Destructors --------------------------------------------------- 

// Returns a Graph pointing to a newly created GraphObj representing a graph having n
// vertices and no edges.
Graph newGraph(int n); 

// Frees all heap memory associated with the Graph *pG, 
// then sets the handle *pG to NULL. 
void freeGraph(Graph* pG);

// Access functions ----------------------------------------------------------- 

// Returns the corresponding field values.
int getOrder(Graph G);

// Returns the corresponding field values.
int getSize(Graph G);

// Return the parent of vertex 𝑢 in the BFS tree 
// created by BFS(), or NIL if BFS() has not yet been called. Precondition: 1 ≤ 𝑢 ≤ getOrder(𝐺).
int getParent(Graph G, int u);

// Returns the corresponding field values. Precondition: 1 <= u <= n = getOrder(G) 
int getDiscover(Graph G, int u);

// Returns the corresponding field values. Precondition: 1 <= u <= n = getOrder(G) 
int getFinish(Graph G, int u); 

// Manipulation procedures ---------------------------------------------------- 

// Inserts a new edge joining 𝑢 to 𝑣, i.e. 𝑢 is added to the adjacency list of 𝑣, and 𝑣 to the adjacency list of u
// Precondition: two int arguments must lie in the range 1 to getOrder(G). 
void addEdge(Graph G, int u, int v); 

// Inserts a new directed edge from 𝑢 to 𝑣, i.e. 𝑣 is added to the adjacency List of 𝑢 (but not 𝑢 to the adjacency 
// List of 𝑣). Precondition: two int arguments must lie in the range 1 to getOrder(G).
void addArc(Graph G, int u, v);

// Performs the depth first search algorithm on G.
void DFS(Graph G, List S);

// A recursive function that visit a vertex in a Graph G.
void Visit(Graph G, int u, int* time, List S);

// Other operations ----------------------------------------------------------- 

// Returns a reference to a new graph object representing the transpose of G.
Graph transpose(Graph G);

// Returns a reference to a new graph that is a copy of G.
Graph copyGragh(Graph G);

// Prints the adjacency list representation of 𝐺 to the file pointed to by out.
void printGraph(FILE* out, Graph G);

#endif