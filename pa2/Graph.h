/*** 
* Peter Liang
* xliang41
* 2024 Fall CSE 101 PA2
* Graph.h
* Header file for Graph ADT. 
***/


#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

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

// Returns the source vertex most recently used in function BFS(), or NIL if 
// BFS() has not yet been called. Precondition 1 ≤ 𝑢 ≤ getOrder(𝐺).
int getSource(Graph G); 

// Return the parent of vertex 𝑢 in the BFS tree 
// created by BFS(), or NIL if BFS() has not yet been called. Precondition 1 ≤ 𝑢 ≤ getOrder(𝐺).
int getParent(Graph G, int u);

// Returns the distance from the most recent BFS source to vertex 𝑢, 
// or INF if BFS() has not yet been called. Precondition 1 ≤ 𝑢 ≤ getOrder(𝐺).
int getDist(Graph G, int u); 

// Appends to the List 𝐿 the vertices of a shortest path in 𝐺 from source to 𝑢, 
// or appends to 𝐿 the value NIL if no such path exists. Precondition getSource(G)!=NIL, so BFS() must be called
// before getPath() is called.
void getPath(List L, Graph G, int u); 

// Manipulation procedures ---------------------------------------------------- 

// deletes all edges of 𝐺, restoring it to its 
// original (no edge) state.
void makeNull(Graph G); 

// Inserts a new edge joining 𝑢 to 𝑣, i.e. 𝑢 is added to the adjacency list of 𝑣, and 𝑣 to the adjacency list of u
// Precondition: two int arguments must lie in the range 1 to getOrder(G). 
void addEdge(Graph G, int u, int v); 

// Inserts a new directed edge from 𝑢 to 𝑣, i.e. 𝑣 is added to the adjacency List of 𝑢 (but not 𝑢 to the adjacency 
// List of 𝑣). Precondition: two int arguments must lie in the range 1 to getOrder(G).
void addArc(Graph G, int u, v);

// Runs the BFS algorithm on the Graph 𝐺 with source 𝑠, 
// setting the color, distance, parent, and source fields of 𝐺 accordingly.  
// It also has the precondition that the int argument 𝑠 lies in the range 1 to getOrder(G).  
void BFS(Graph G, int s);

// Other operations ----------------------------------------------------------- 

// Prints the adjacency list representation of 𝐺 to the file pointed to by out.
void printGraph(FILE* out, Graph G);

#endif