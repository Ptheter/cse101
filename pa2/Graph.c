/***
* Peter Liang
* xliang41
* 2024 Fall CSE 101 PA2
* Graph.c
* Implementation file for Graph ADT.
***/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"
#include "List.h"


typedef struct GraphObj {
    List* adjList;
    int* color;
    int* parent;
    int* distance;
    int size;
    int order;
    int source;
} GraphObj;


// Constructors-Destructors ---------------------------------------------------

// Returns a Graph pointing to a newly created GraphObj representing a graph having n
// vertices and no edges.
Graph newGraph(int n){
    Graph G = malloc(sizeof(GraphObj));
    G->adjList = calloc(n+1, sizeof(List));
    G->color = calloc(n+1, sizeof(int));
    G->parent = calloc(n+1, sizeof(int));
    G->distance = calloc(n+1, sizeof(int));
    G->size = 0;
    G->order = n;
    G->source = NIL;
    for (int i=1; i<=n; i++) {
        G->adjList[i] = newList();
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->distance[i] = INF;
    }

    return G;
}

// Frees all heap memory associated with the Graph *pG,
// then sets the handle *pG to NULL.
void freeGraph(Graph* pG){
    Graph g = *pG;
    if ( pG!=NULL && *pG!=NULL ){
        for ( int i=1; i<=(g->order); i++){
            freeList(&(g->adjList[i]));
        }
        free(g->adjList);
        free(g->color);
        free(g->parent);
        free(g->distance);
        free(*pG);
        *pG = NULL;
    }
}


// Access functions -----------------------------------------------------------

// Returns the corresponding field values.
int getOrder(Graph G){
    if ( G==NULL ){
        fprintf(stderr, "Error: getOrder() called on NULL Graph.\n");
        exit(EXIT_FAILURE);
    }
    return G->order;
}

// Returns the corresponding field values.
int getSize(Graph G){
    if ( G==NULL ){
        fprintf(stderr, "Error: getSize() called on NULL Graph.\n");
        exit(EXIT_FAILURE);
    }
    return G->size;
}

// Returns the source vertex most recently used in function BFS(), or NIL if
// BFS() has not yet been called. Precondition 1 ≤ 𝑢 ≤ getOrder(𝐺).
int getSource(Graph G){
    if ( G==NULL ){
        fprintf(stderr, "Error: getSource() called on NULL Graph.\n");
        exit(EXIT_FAILURE);
    }
    return G->source;
}

// Return the parent of vertex 𝑢 in the BFS tree
// created by BFS(), or NIL if BFS() has not yet been called. Precondition 1 ≤ 𝑢 ≤ getOrder(𝐺).
int getParent(Graph G, int u){
    if ( G==NULL ){
        fprintf(stderr, "Error: getParent() called on NULL Graph.\n");
        exit(EXIT_FAILURE);
    }
    if ( u<1 || u>getOrder(G) ){
        fprintf(stderr, "Error: getParent() called with vertex out of range.\n");
        exit(EXIT_FAILURE);
    }
    return G->parent[u];
}

// Returns the distance from the most recent BFS source to vertex 𝑢,
// or INF if BFS() has not yet been called. Precondition 1 ≤ 𝑢 ≤ getOrder(𝐺).
int getDist(Graph G, int u){
    if ( G==NULL ){
        fprintf(stderr, "Error: getDist() called on NULL Graph.\n");
        exit(EXIT_FAILURE);
    }
    if ( u<1 || u>getOrder(G) ){
        fprintf(stderr, "Error: getDist() called with vertex out of range.\n");
        exit(EXIT_FAILURE);
    }
    if ( getSource(G)==NIL ){
        return INF;
    }
    else{
        return G->distance[u];
    }
}

// Appends to the List 𝐿 the vertices of a shortest path in 𝐺 from source to 𝑢,
// or appends to 𝐿 the value NIL if no such path exists. Precondition getSource(G)!=NIL, so BFS() must be called
// before getPath() is called.
void getPath(List L, Graph G, int u){
    if ( G==NULL ){
        fprintf(stderr, "Error: getPath() called on NULL Graph.\n");
        exit(EXIT_FAILURE);
    }
    if ( u<1 || u>getOrder(G) ){
        fprintf(stderr, "Error: getPath() called with vertex out of range.\n");
        exit(EXIT_FAILURE);
    }
    if ( getSource(G)==NIL ){
        fprintf(stderr, "Error: getPath() called before BFS().\n");
        exit(EXIT_FAILURE);
    }
    if ( u==(G->source) ){
        append(L, u);
    }
    else if ( G->parent[u]==NIL ){
        append(L, NIL);
    }
    else{
        getPath(L, G, G->parent[u]);
        append(L, u);
    }
}


// Manipulation procedures ----------------------------------------------------

// Deletes all edges of 𝐺, restoring it to its
// original (no edge) state.
void makeNull(Graph G){
    for ( int i=1; i<=(G->order); i++){
        clear(G->adjList[i]);
    }
    G->size = 0;
}

// Inserts a new edge joining 𝑢 to 𝑣, i.e. 𝑢 is added to the adjacency list of 𝑣, and 𝑣 to the adjacency list of u
// Precondition: two int arguments must lie in the range 1 to getOrder(G).
void addEdge(Graph G, int u, int v){
    if ( (u<1 || u>getOrder(G)) || (v<1 || v>getOrder(G)) ){
        fprintf(stderr, "Error: addEdge() called on out of range vertex or edge.\n");
        exit(EXIT_FAILURE);
    }
    List U = G->adjList[u];
    moveFront(U);
    while ( index(U)!=-1 && get(U)<v ){
        moveNext(U);
    }
    if ( index(U)==-1 ){
        append(U, v);
    }
    else{
        insertBefore(U, v);
    }
    List V = G->adjList[v];
    moveFront(V);
    while ( index(V)!=-1 && get(V)<u ){
        moveNext(V);
    }
    if ( index(V)==-1 ){
        append(V, u);
    }
    else{
        insertBefore(V, u);
    }

    G->size += 1;
}

// Inserts a new directed edge from 𝑢 to 𝑣, i.e. 𝑣 is added to the adjacency List of 𝑢 (but not 𝑢 to the adjacency
// List of 𝑣). Precondition: two int arguments must lie in the range 1 to getOrder(G).
void addArc(Graph G, int u, int v){
    if ( (u<1 || u>getOrder(G)) || (v<1 || v>getOrder(G)) ){
        fprintf(stderr, "Error: addArc() called on out of range vertex or edge.\n");
        exit(EXIT_FAILURE);
    }
    List U = G->adjList[u];
    moveFront(U);
    while ( index(U)!=-1 && get(U)<v ){
        moveNext(U);
    }
    if ( index(U)==-1 ){
        append(U, v);
    }
    else{
        insertBefore(U, v);
    }
    G->size += 1;
}

// Runs the BFS algorithm on the Graph 𝐺 with source 𝑠,
// setting the color, distance, parent, and source fields of 𝐺 accordingly.
// It also has the precondition that the int argument 𝑠 lies in the range 1 to getOrder(G).
void BFS(Graph G, int s){
    if ( s<1 || s>getOrder(G) ){
        fprintf(stderr, "Error: BFS() called with vertex out of range.\n");
        exit(EXIT_FAILURE);
    }
    for ( int i=1; i<=(G->order); i++){
        G->color[i] = WHITE;
        G->distance[i] = INF;
        G->parent[i] = NIL;
    }
    G->color[s] = GRAY;
    G->distance[s] = 0;
    G->parent[s] = NIL;
    G->source = s;

    List Q = newList();
    append(Q, s);
    while ( length(Q)>0 ){
        int x = front(Q);
        deleteFront(Q);
        List neighbors = G->adjList[x];
        for ( moveFront(neighbors); index(neighbors)>=0; moveNext(neighbors) ){
            int y = get(neighbors);
            if ( (G->color[y])==WHITE ){
                G->color[y] = GRAY;
                G->parent[y] = x;
                G->distance[y] = G->distance[x] + 1;
                append(Q, y);
            }
        }
        G->color[x] = BLACK;
    }
    freeList(&Q);
}


// Other operations -----------------------------------------------------------

// Prints the adjacency list representation of 𝐺 to the file pointed to by out.
void printGraph(FILE* out, Graph G){
    for ( int i=1; i<=getOrder(G); i++){
        List N = G->adjList[i];
        fprintf(out, "%d: ", i);
        for ( moveFront(N); index(N)>=0; moveNext(N)){
            fprintf(out, "%d ", get(N));
        }
        fprintf(out, "\n");
    }
}