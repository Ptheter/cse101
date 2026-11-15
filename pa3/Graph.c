/***
* Peter Liang
* xliang41
* 2024 Fall CSE 101 PA3
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
    int* discover;
    int* finish;
    int size;
    int order;
} GraphObj;


// Constructors-Destructors ---------------------------------------------------

// Returns a Graph pointing to a newly created GraphObj representing a graph having n
// vertices and no edges.
Graph newGraph(int n){
    Graph G = malloc(sizeof(GraphObj));
    G->adjList = calloc(n+1, sizeof(List));
    G->color = calloc(n+1, sizeof(int));
    G->parent = calloc(n+1, sizeof(int));
    G->discover = calloc(n+1, sizeof(int));
    G->finish = calloc(n+1, sizeof(int));
    G->size = 0;
    G->order = n;
    for (int i=1; i<=n; i++) {
        G->adjList[i] = newList();
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
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
        free(g->discover);
        free(g->finish);
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

// Returns the corresponding field values. Precondition: 1 <= u <= n = getOrder(G)
int getDiscover(Graph G, int u){
    if ( G==NULL ){
        fprintf(stderr, "Error: getDiscover() called on NULL Graph.\n");
        exit(EXIT_FAILURE);
    }
    if ( u<1 || u>getOrder(G) ){
        fprintf(stderr, "Error: getDiscover() called with vertex out of range.\n");
        exit(EXIT_FAILURE);
    }
    return G->discover[u];
}

// Returns the corresponding field values. Precondition: 1 <= u <= n = getOrder(G)
int getFinish(Graph G, int u){
    if ( G==NULL ){
        fprintf(stderr, "Error: getFinish() called on NULL Graph.\n");
        exit(EXIT_FAILURE);
    }
    if ( u<1 || u>getOrder(G) ){
        fprintf(stderr, "Error: getFinish() called with vertex out of range.\n");
        exit(EXIT_FAILURE);
    }
    return G->finish[u];
}


// Manipulation procedures ----------------------------------------------------

// Inserts a new edge joining 𝑢 to 𝑣, i.e. 𝑢 is added to the adjacency list of 𝑣, and 𝑣 to the adjacency list of u
// Precondition: two int arguments must lie in the range 1 to getOrder(G).
void addEdge(Graph G, int u, int v){
    if ( (u<1 || u>getOrder(G)) || (v<1 || v>getOrder(G)) ){
        fprintf(stderr, "Error: addEdge() called on out of range vertex or edge.\n");
        exit(EXIT_FAILURE);
    }
    addArc(G, u, v);
    addArc(G, v, u);
    G->size -= 1;
}

// Inserts a new directed edge from 𝑢 to 𝑣, i.e. 𝑣 is added to the adjacency List of 𝑢 (but not 𝑢 to the adjacency
// List of 𝑣). Precondition: two int arguments must lie in the range 1 to getOrder(G).
void addArc(Graph G, int u, int v){
    if ( (u<1 || u>getOrder(G)) || (v<1 || v>getOrder(G)) ) {
        fprintf(stderr, "Error: addArc() called on out of range vertex or edge.\n");
        exit(EXIT_FAILURE);
    }
    List L = G->adjList[u];
    if ( length(L)==0 ){
        append(L, v);
    }
    else{
        for ( moveFront(L); index(L)>=0; moveNext(L) ){
            if ( v<get(L) ){
                insertBefore(L, v);
                break;
            }
            else if ( v==get(L) ){
                return;
            }
        }
        if ( index(L)<0 ){
            append(L, v);
        }
    }
    G->size += 1;
}

// Performs the depth first search algorithm on G.
void DFS(Graph G, List S){
    if ( length(S)!=getOrder(G) ){
        fprintf(stderr, "Error: List S length must be equal to the number of vertices in the graph G.\n");
        exit(EXIT_FAILURE);
    }

    for ( int i=1; i<=getOrder(G); i++ ){
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
    }

    int time = 0;
    List copy = copyList(S);
    clear(S);
    moveFront(copy);
    while ( index(copy)>=0 ){
        int u = get(copy);
        if ( G->color[u]==WHITE ){
            Visit(G, u, &time, S);
        }
        moveNext(copy);
    }
    freeList(&copy);
}

// A recursive function that visit a vertex in a Graph G.
void Visit(Graph G, int u, int* time, List S){
    G->discover[u] = ++(*time);
    G->color[u] = GRAY;
    List neighbors = G->adjList[u];
    moveFront(neighbors);
    while ( index(neighbors)>=0 ){
        int v = get(neighbors);
        if ( G->color[v]==WHITE ){
            G->parent[v] = u;
            Visit(G, v, time, S);
        }
        moveNext(neighbors);
    }
    G->color[u] = BLACK;
    G->finish[u] = ++(*time);
    prepend(S, u);
}


// Other operations -----------------------------------------------------------

// Returns a reference to a new graph object representing the transpose of G.
Graph transpose(Graph G){
    int n = getOrder(G);
    Graph T = newGraph(n);
    for ( int i=1; i<=n; i++ ){
        List neighbors = G->adjList[i];
        for ( moveFront(neighbors); index(neighbors)>=0; moveNext(neighbors) ){
            int j = get(neighbors);
            addArc(T, j, i);
        }
    }
    return T;
}

// Returns a reference to a new graph that is a copy of G.
Graph copyGragh(Graph G){
    int n = getOrder(G);
    Graph C = newGraph(n);
    for ( int i=1; i<=n; i++ ){
        List neighbors = G->adjList[i];
        for ( moveFront(neighbors); index(neighbors)>=0; moveNext(neighbors) ){
            int j = get(neighbors);
            addArc(C, i, j);
        }
    }
    return C;
}

// Prints the adjacency list representation of 𝐺 to the file pointed to by out.
void printGraph(FILE* out, Graph G){
    for ( int i=1; i<=getOrder(G); i++){
        List L = G->adjList[i];
        fprintf(out, "%d: ", i);
        for ( moveFront(L); index(L)>=0; moveNext(L)){
            fprintf(out, "%d ", get(L));
        }
        fprintf(out, "\n");
    }
}