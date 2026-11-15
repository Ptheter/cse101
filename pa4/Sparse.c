/*** 
* Peter Liang
* xliang41
* 2024 Fall CSE 101 PA4
* Sparse.c
* Client module for Matrix ADT. 
***/


#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

int main(int argc, char* argv[]){
    if (argc != 3) {
        fprintf(stderr, "Usage: Sparse <input file> <output file>\n");
        exit(EXIT_FAILURE);
    }
    FILE* in = fopen(argv[1], "r");
    if (in == NULL) {
        fprintf(stderr, "Unable to open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    FILE* out = fopen(argv[2], "w");
    if (out == NULL) {
        fprintf(stderr, "Unable to open file %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    int n, a, b;
    fscanf(in, "%d %d %d", &n, &a, &b);
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);

    for (int i=0; i<a; i++){
        int row, column;
        double value;
        fscanf(in, "%d %d %lf", &row, &column, &value);
        changeEntry(A, row, column, value);
    }

    for (int i=0; i<b; i++){
        int row, column;
        double value;
        fscanf(in, "%d %d %lf", &row, &column, &value);
        changeEntry(B, row, column, value);
    }

    fprintf(out, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(out, A);

    fprintf(out, "\nB has %d non-zero entries:\n", NNZ(B));
    printMatrix(out, B);
    fprintf(out, "\n");

    //(1.5)*A
    fprintf(out, "(1.5)*A =\n");
    Matrix C = scalarMult(1.5, A);
    printMatrix(out, C);
    fprintf(out, "\n");
    freeMatrix(&C);

    // A + B
    fprintf(out, "A+B =\n");
    Matrix D = sum(A, B);
    printMatrix(out, D);
    fprintf(out, "\n");
    freeMatrix(&D);

    // A+A 
    fprintf(out, "A+A =\n");
    Matrix E = sum(A, A);
    printMatrix(out, E);
    fprintf(out, "\n");
    freeMatrix(&E);

    // B-A
    fprintf(out, "B-A =\n");
    Matrix F = diff(B, A);
    printMatrix(out, F);
    fprintf(out, "\n");
    freeMatrix(&F);

    // A-A
    fprintf(out, "A-A =\n");
    Matrix G = diff(A, A);
    printMatrix(out, G);
    fprintf(out, "\n");
    freeMatrix(&G);

    // Transpose(A)
    fprintf(out, "Transpose(A) =\n");
    Matrix H = transpose(A);
    printMatrix(out, H);
    fprintf(out, "\n");
    freeMatrix(&H);

    // A*B
    fprintf(out, "A*B =\n");
    Matrix I = product(A, B);
    printMatrix(out, I);
    fprintf(out, "\n");
    freeMatrix(&I);

    // B*B
    fprintf(out, "B*B =\n");
    Matrix J = product(B, B);
    printMatrix(out, J);
    fprintf(out, "\n");
    freeMatrix(&J);

    freeMatrix(&A);
    freeMatrix(&B);

    fclose(in);
    fclose(out);
    return 0;
    }