/*** 
* Peter Liang
* xliang41
* 2024 Fall CSE 101 PA4
* Matrix.c
* Implementation file for Matrix ADT. 
***/


#include <stdlib.h>
#include <stdio.h>

#include "List.h"
#include "Matrix.h"


// structs --------------------------------------------------------------------
// private Entry type
typedef struct EntryObj* Entry;

// private EntryObj type
typedef struct EntryObj{
    int column; 
    double value;
}EntryObj;

Entry newEntry(int c, double v){
    Entry E = malloc(sizeof(EntryObj));
    E->column = c;
    E->value = v;
    return E;
}

void freeEntry(Entry* pE){
    if ( pE!=NULL && *pE!=NULL ){
        free(*pE);
        *pE = NULL;
    }
}

typedef struct MatrixObj{
    int size;
    int NNZ;
    List* rows;
}MatrixObj;

// newMatrix() 
// Returns a reference to a new nXn Matrix object in the zero state. 
Matrix newMatrix(int n){
    Matrix M = malloc(sizeof(MatrixObj));
    M->size = n;
    M->NNZ = 0;
    M->rows = calloc(n+1, sizeof(List));
    for (int i=1; i<=n; i++){
        M->rows[i] = newList()
    }
    return M;
}

// freeMatrix() 
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM){
    if ( pM!=NULL && *pM!=NULL ){
        for (int i=1; i<=((*pM)->size); i++){
            List row = (*pM)->rows[i];
            for (moveFront(row); index(row)>=0; moveNext(row)){
                Entry E = get(row);
                freeEntry(&E);
            }
            freeList(&((*pM)->rows[i]));
        }
        free((*pM)->rows);
        free(*pM);
        *pM = NULL;
    }
}

// Access functions ----------------------------------------------------------- 

// size() 
// Return the size of square Matrix M.
int size(Matrix M){
    return M->size;
}

// NNZ() 
// Return the number of non-zero elements in M.
int NNZ(Matrix M){
    return M->NNZ;
}

// equals() 
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B){
    if (A==NULL || B==NULL){
        fprintf(stderr, "Calling equals() on empty matrix.\n");
        exit(EXIT_FAILURE);
    }
    if (size(A) != size(B)){
        return 0;
    }
    for (int i=1; i<=(A->size); i++){
        if (length(A->rows[i]) != length(B->rows[i])){
            return 0;
        }
        moveFront(A->rows[i]);
        moveFront(B->rows[i]);
        while (index(A->rows[i]>=0 && index(B->rows[i]>=0))){
            Entry Ea = (Entry) get(A->rows[i]);
            Entry Eb = (Entry) get(B->rows[i]);
            if ((Ea->column != Eb->column) || (Ea->value != Eb->value)){
                return 0;
            }
            moveNext(A->rows[i]);
            moveNext(B->rows[i]);
        }
    }
    return 1;
}

// Manipulation procedures ---------------------------------------------------- 

// makeZero() 
// Re-sets M to the zero Matrix state. 
void makeZero(Matrix M){
    for (int i=1; i<=(M->size); i++){
        List row = M->rows[i];
        if (row != NULL){
            clear(row);
        }
    }
    M->NNZ = 0;
}

// changeEntry() 
// Changes the ith row, jth column of M to the value x. 
// Pre: 1<=i<=size(M), 1<=j<=size(M) 
void changeEntry(Matrix M, int i, int j, double x){
    if (M == NULL){
        fprintf(stderr, "Error: calling changeEntry() on NULL Matrix.\n");
        exit(EXIT_FAILURE);
    }
    if (i<1 || i>(M->size) || j<1 || j>(M->size)){
        fprintf(stderr, "Error: calling out of bound rows/columns.\n");
        exit(EXIT_FAILURE);
    }
    List row = M->rows[i];
    moveFront(row);
    while (index(row)>=0){
        Entry E = (Entry) get(row);
        if ((E->column) == j){
            if (x != 0.0){
                E->value = x;
                return;
            }
            else{
                delete(row);
                freeEntry(&E);
                M->NNZ -= 1;
                return;
            }
        }
        else if ((E->column) > j){
            if (x != 0.0){
                insertBefore(row, newEntry(j, x));
                M->NNZ += 1;
                return;
            }
            else{
                return;
            }
        }
        moveNext(row);
    }
    if (x != 0.0){
        append(row, newEntry(j, x));
        M->NNZ += 1;
    }
}

// Matrix Arithmetic operations ----------------------------------------------------

// copy() 
// Returns a reference to a new Matrix object having the same entries as A. 
Matrix copy(Matrix A){
    if (A == NULL){
        fprintf(stderr, "Error: calling copy() on NULL matrix.\n");
        exit(EXIT_FAILURE);
    }
    Matrix B = newMatrix((A->size));
    for (int i=1; i<=(A->size); i++){
        List rowA = A->rows[i];
        moveFront(rowA);
        while (index(rowA) >= 0){
            Entry E = (Entry) get(rowA);
            changeEntry(B, i, E->column, E->value);
            moveNext(rowA);
        }
    }
    return B;
}

// transpose() 
// Returns a reference to a new Matrix object representing the transpose of A. 
Matrix transpose(Matrix A){
    if (A == NULL){
        fprintf(stderr, "Error: calling transpose() on NULL matrix.\n");
        exit(EXIT_FAILURE);
    }
    Matrix T = newMatrix((A->size));
    for (int i=1; i<=(A->size); i++){
        List rowA = A->rows[i];
        moveFront(rowA);
        while (index(rowA) >= 0){
            Entry E = (Entry) get(rowA);
            changeEntry(T, E->column, i, E->value);
            moveNext(rowA);
        }
    }
    return T;
}

// scalarMult() 
// Returns a reference to a new Matrix object representing xA. 
Matrix scalarMult(double x, Matrix A){
    if (A == NULL){
        fprintf(stderr, "Error: calling scalarMult() on NULL matrix.\n");
        exit(EXIT_FAILURE);
    }
    Matrix S = newMatrix((A->size));
    for (int i=1; i<=(A->size); i++){
        List rowA = A->rows[i];
        moveFront(rowA);
        while (index(rowA) >= 0){
            Entry E = (Entry) get(rowA);
            changeEntry(S, i, E->column, (E->value)*x);
            moveNext(rowA);
        }
    }
    return S;
}

// sum() 
// Returns a reference to a new Matrix object representing A+B. 
// pre: size(A)==size(B) 
Matrix sum(Matrix A, Matrix B){
    if (A == NULL || B == NULL){
        fprintf(stderr, "Error: calling sum() on NULL matrix.\n");
        exit(EXIT_FAILURE);
    }
    if ((A->size) != (B->size)){
        fprintf(stderr, "Error: cannot perform sum() with two different size matrices.\n")
        exit(EXIT_FAILURE);
    }
    if (equals(A, B)){
        return scalarMult(2.0, A);
    }
    Matrix C = newMatrix((A->size));
    for (int i=1; i<=(A->size); i++){
        List rowA = A->rows[i];
        List rowB = B->rows[i];
        List rowC = C->rows[i];
        moveFront(rowA);
        moveFront(rowB);
        while ((index(rowA) >= 0) && (index(rowB) >= 0)){
            Entry Ea = (Entry) get(rowA);
            Entry Eb = (Entry) get(rowB);
            if ((Ea->column) < (Eb->column)){
                append(rowC, newEntry((Ea->column), (Ea->value)));
                C->NNZ += 1;
                moveNext(rowA);
            }
            else if ((Ea->column) > (Eb->column)){
                append(rowC, newEntry((Eb->column), (Eb->value)));
                C->NNZ += 1;
                moveNext(rowB);
            }
            else{
                if (((Ea->value) + (Eb->value)) != 0){
                    append(rowC, newEntry((Ea->column), ((Ea->value) + (Eb->value))));
                    C->NNZ += 1;
                }
                moveNext(rowA);
                moveNext(rowB);
            }
        }
        while ((index(rowA) >= 0)){
            Entry Ea = (Entry) get(rowA);
            append(rowC, newEntry((Ea->column), (Ea->value)));
            C->NNZ += 1;
            moveNext(rowA);
        }
        while ((index(rowB) >= 0)){
            Entry Eb = (Entry) get(rowB);
            append(rowC, newEntry((Eb->column), (Eb->value)));
            C->NNZ += 1;
            moveNext(rowB);
        }
    }
    return C;
}

// diff() 
// Returns a reference to a new Matrix object representing A-B. 
// pre: size(A)==size(B) 
Matrix diff(Matrix A, Matrix B){
    if (A == NULL || B == NULL){
        fprintf(stderr, "Error: calling diff() on NULL matrix.\n");
        exit(EXIT_FAILURE);
    }
    if ((A->size) != (B->size)){
        fprintf(stderr, "Error: cannot perform diff() with two different size matrices.\n")
        exit(EXIT_FAILURE);
    }
    if (equals(A, B)){
        Matrix Ca = copy(A);
        makeZero(Ca);
        return Ca;
    }
    return sum(A, scalarMult(-1.0, B));
}

// vectorDot()
// Returns the dot product of List P and List Q. 
double vectorDot(List P, List Q){
    if (P == NULL || Q == NULL){
        fprintf(stderr, "Error: calling vectorDot() on NULL lists.\n");
        exit(EXIT_FAILURE);
    }
    moveFront(P);
    moveFront(Q);
    double dot_product = 0.0;
    while ((index(P) >= 0) && (index(Q) >= 0)){
        Entry Ep = (Entry) get(P);
        Entry Eq = (Entry) get(Q);
        if ((Ep->column) == (Eq->column)){
            dot_product += (Ep->value * Eq->value);
            moveNext(P);
            moveNext(Q);
        }
        else if ((Ep->column) > (Eq->column)){
            moveNext(Q);
        }
        else{
            moveNext(P);
        }
    }
    return dot_product;
}

// product() 
// Returns a reference to a new Matrix object representing AB 
// pre: size(A)==size(B) 
Matrix product(Matrix A, Matrix B){
    if (A == NULL || B == NULL){
        fprintf(stderr, "Error: calling product() on NULL matrix.\n");
        exit(EXIT_FAILURE);
    }
    if ((A->size) != (B->size)){
        fprintf(stderr, "Error: cannot perform product() with two different size matrices.\n")
        exit(EXIT_FAILURE);
    }
    Matrix P = newMatrix(A->size);
    Matrix Bt = transpose(B);
    if ((A->NNZ==0) && (B->NNZ==0)){
        return P;
    }
    for (int i=1; i<=(A->size); i++){
        List rowA = A->rows[i];
        if (length(rowA) > 0){
            for (int j=1; j<=(Bt->size); j++){
                List rowB = Bt->rows[j];
                if (length(rowB) > 0){
                    double dot_product = vectorDot(rowA, rowB);
                    if (dot_product != 0.0){
                        Entry Ep = newEntry(j, dot_product);
                        append(P->rows[i], Ep);
                        P->NNZ += 1;
                    }
                } 
            }
        }
    }
    freeMatrix(&Bt);
    return P;
}

// printMatrix() 
// Prints a string representation of Matrix M to filestream out. Zero rows  
// are not printed.  Each non-zero row is represented as one line consisting  
// of the row number, followed by a colon, a space, then a space separated  
// list of pairs "(col, val)" giving the column numbers and non-zero values  
// in that row. The double val will be rounded to 1 decimal point. 
void printMatrix(FILE* out, Matrix M){
    if (out==NULL || M==NULL){
      fprintf(stderr, "Error: printMatrix() called with NULL parameters.\n");
      exit(EXIT_FAILURE);
    }
    for (int i=1; i<=size(M); i++){
        if (length(M->rows[i]) > 0){
            fprintf(out, "%d: ", i);
            moveFront(M->rows[i]);
            while ((index(M->rows[i])) >= 0){
                Entry E = (Entry) get(M->rows[i]);
                fprintf(out, "(%d, %.1f) ", E->column, E->value);
                moveNext(M->rows[i]);
            }
            fprintf(out, "\n");
        }
    }
}