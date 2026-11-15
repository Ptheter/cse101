/*** 
* Peter Liang
* xliang41
* 2024 Fall CSE 101 PA2
* FindPath.c
* Client module of Graph ADT. 
***/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"List.h"
#include"Graph.h"


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

    int n;
    fscanf(in, "%d", &n);
    Graph G = newGraph(n);
    int u, v;
    while ( fscanf(in, "%d %d", &u, &v)==2 ){
        if ( u==0 && v==0 ){
            break;
        }
        addEdge(G, u, v);
    }

    printGraph(out, G);

    while ( fscanf(in, "%d %d", &u, &v)==2 ){
        if ( u==0 && v==0 ){
            break;
        }
        BFS(G, u);
        List L = newList();
        if ( getDist(G, v)==INF ){
            fprintf(out, "The distance from %d to %d is infinity\n", u, v);
            fprintf(out, "No %d-%d path exists\n", u, v);
            fprintf(out, "\n");
        } else{
            fprintf(out, "The distance from %d to %d is %d\n", u, v, getDist(G, v));
            fprintf(out, "A shortest %d-%d path is: ", u, v);
            getPath(L, G, v);
            printList(out, L);
            fprintf(out, "\n");
        }
        freeList(&L);
    }

    freeGraph(&G);
    fclose(in);
    fclose(out);

    return 0;
}