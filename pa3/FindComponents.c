/***
* Peter Liang
* xliang41
* 2024 Fall CSE 101 PA3
* FindComponents.c
* Main program that determines the strongly connected components of a Graph.
***/


#include <stdio.h>
#include <stdlib.h>

#include "List.h"
#include "Graph.h"


int main(int argc, char* argv[]){
    FILE *in, *out;
    // Check command line for correct number of arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // Open files for reading and writing
    in = fopen(argv[1], "r");
    if (in == NULL) {
        fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    out = fopen(argv[2], "w");
    if (out == NULL) {
        fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
        fclose(in);
        exit(1);
    }

    Graph G, T;
    List L = newList();
    int n, u, v, x;
    int count = 0;
    fscanf(in, "%d", &n);
    G = newGraph(n);
    while ( fscanf(in, "%d %d", &u, &v)==2 ){
        if ( u==0 && v==0 ){
            break;
        }
        addArc(G, u, v);
    }
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
    fprintf(out, "\n");

    T = transpose(G);
    for ( int i=1; i<=n; i++ ){
        append(L, i);
    }
    DFS(G, L);
    DFS(T, L);

    for ( int i=1; i<=n; i++ ){
        if ( getParent(T, i)==NIL ){
            x += 1;
        }
    }
    List* scc = calloc(x, sizeof(List));
    for ( int i=0; i<x; i++){
        scc[i] = newList();
    }
    for ( moveBack(L); index(L)>=0; movePrev(L) ){
        int comp = get(L);
        prepend(scc[count], comp);
        if ( getParent(T, comp)==NIL ){
            count += 1;
        }
    }

    fprintf(out, "G contains %d strongly connected components:\n", x);
    for ( int i=0; i<x; i++ ){
        fprintf(out, "Component %d: ", i+1);
        printList(out, scc[i]);
        fprintf(out, "\n");
        freeList(&scc[i]);
    }

    freeGraph(&G);
    freeGraph(&T);
    freeList(&L);
    free(scc);
    fclose(in);
    fclose(out);
    return 0;

}