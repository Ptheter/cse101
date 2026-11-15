/***
* Peter Liang
* xliang41
* 2024 Fall CSE 101 PA1
* List.c
* Implementation file for List ADT.
***/

#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "List.h"


// structs --------------------------------------------------------------------
// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj{
   ListElement data;
   Node previous;
   Node next;
} NodeObj;

// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int length;
   int index;
} ListObj;


// Constructors-Destructors ---------------------------------------------------
// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(ListElement data){
    Node N = malloc(sizeof(NodeObj));
    assert( N!=NULL );
    N->data = data;
    N->previous = NULL;
    N->next = NULL;
    return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
    if ( pN!=NULL && *pN!=NULL ){
        free(*pN);
        *pN = NULL;
    }
}

// newList()
// Returns reference to new empty List object.
List newList(void){
    List L;
    L = malloc(sizeof(ListObj));
    assert( L!=NULL );
    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->index = -1;
    return (L);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL){
    if ( pL!=NULL && *pL!=NULL){
        clear(*pL);
        free(*pL);
        *pL=NULL;
    }
}


// Access functions -----------------------------------------------------------
// Returns the number of elements in L.
int length(List L){
    if ( L==NULL ){
        fprintf(stderr, "List Error: calling length() on NULL list.\n");
        exit(EXIT_FAILURE);
    }
    return(L->length);
}

// Returns index of cursor element if defined, -1 otherwise.
int index(List L){
    if ( L==NULL ){
        fprintf(stderr, "List Error: calling index() on NULL list.\n");
        exit(EXIT_FAILURE);
    }
    return(L->index);
}

// Returns the front element of L. Pre: length()>0.
int front(List L){
    if ( L==NULL ){
        fprintf(stderr, "List Error: calling front() on NULL list.\n");
        exit(EXIT_FAILURE);
    }

    return (L->front->data);
}

// Returns the back element of L. Pre: length()>0.
int back(List L){
    if ( L==NULL ){
        fprintf(stderr, "List Error: calling back() on NULL list.\n");
        exit(EXIT_FAILURE);
    }

    return(L->back->data);

}

// Returns cursor element of L. Pre: length()>0, index()>=0.
int get(List L){
    if ( L==NULL ){
        fprintf(stderr, "List Error: calling get() on NULL list.\n");
        exit(EXIT_FAILURE);
    }
    if ( L->cursor == NULL ){
        fprintf(stderr, "List Error: calling get() on a NULL cursor.\n");
        exit(EXIT_FAILURE);
    }

    return (L->cursor->data);
}

// Returns true iff Lists A and B contain the same sequence of elements, returns false otherwise.
bool equals(List A, List B){
    if ( A==NULL && B==NULL ){
        return true;
    }
    else if ( A==NULL || B==NULL ){
        return false;
    }
    if ( A->length != B->length ){
        return false;
    }

    moveFront(A);
    moveFront(B);

    while ( index(A)>=0 && index(B)>=0 ){
        if ( get(A)!=get(B) ){
            return false;
        }
        moveNext(A);
        moveNext(B);
    }
    return true;
}


// Manipulation procedures ----------------------------------------------------
// Resets L to its original empty state.
void clear(List L){
    if ( L==NULL ){
        fprintf(stderr, "List Error: calling clear() on NULL list.\n");
        exit(EXIT_FAILURE);
    }
    while ( L->length>0 ){
        deleteFront(L);
    }
    L->cursor = NULL;
    L->index = -1;
}

// Overwrites the cursor element’s data with x. Pre: length()>0, index()>=0.
void set(List L, int x){
    if ( L== NULL ){
        fprintf(stderr, "List Error: calling set() on NULL list.\n");
        exit(EXIT_FAILURE);
    }
    if ( index(L)>-1 ){
        L->cursor->data = x;
    }
}

// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L){
    if ( L== NULL ){
        fprintf(stderr, "List Error: calling moveFront() on NULL list.\n");
        exit(EXIT_FAILURE);
    }
    if ( L->length>0 ){
        L->cursor = L->front;
        L->index = 0;
    }
}

// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L){
    if ( L== NULL ){
        fprintf(stderr, "List Error: calling moveBack() on NULL list.\n");
        exit(EXIT_FAILURE);
    }
    if ( L->length>0 ){
        L->cursor = L->back;
        L->index = (L->length) - 1;
    }
}

// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing.
void movePrev(List L){
    if ( L== NULL ){
        fprintf(stderr, "List Error: calling movePrev() on NULL list.\n");
        exit(EXIT_FAILURE);
    }
    if ( L->cursor!=NULL ){
        if ( L->cursor!=L->front ){
            L->cursor = L->cursor->previous;
            L->index -= 1;
        }
        else {
            L->cursor = NULL;
            L->index = -1;
        }
    }
}

// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing.
void moveNext(List L){
    if ( L== NULL ){
        fprintf(stderr, "List Error: calling moveNext() on NULL list.\n");
        exit(EXIT_FAILURE);
    }
    if ( L->cursor!=NULL ){
        if ( L->cursor!=L->back ){
            L->cursor = L->cursor->next;
            L->index += 1;
        }
        else{
            L->cursor = NULL;
            L->index = -1;
        }
    }
}

// Insert new element into L.  If L is non-empty, insertion takes place before front element.
void prepend(List L, int x){
    if ( L== NULL ){
        fprintf(stderr, "List Error: calling prepend() on NULL list.\n");
        exit(EXIT_FAILURE);
    }
    Node N = newNode(x);
    if ( L->length!=0 ){
        N->next = L->front;
        L->front->previous = N;
        L->front = N;
        if ( L->index!=-1 ){
            (L->index) += 1;
        }
    }
    else{
        L->front = L->back = N;
    }
    (L->length) += 1;
}

// Insert new element into L.  If L is non-empty, insertion takes place after back element.
void append(List L, int x){
    if ( L== NULL ){
        fprintf(stderr, "List Error: calling append() on NULL list.\n");
        exit(EXIT_FAILURE);
    }
    Node N = newNode(x);
    if ( L->length!=0 ){
        N->previous = L->back;
        L->back->next = N;
        L->back = N;
    }
    else{
        L->front = L->back = N;
    }
    (L->length) += 1;
}

// Insert new element before cursor. Pre: length()>0, index()>=0.
void insertBefore(List L, int x){
    if ( L==NULL ){
        fprintf(stderr, "List Error: calling insertBefore() on NULL list.\n");
        exit(EXIT_FAILURE);
    }
    if ( L->cursor==NULL ){
        fprintf(stderr, "List Error: calling insertBefore() on a NULL cursor.\n");
        exit(EXIT_FAILURE);
    }
    if ( L->cursor==L->front ){
        prepend(L, x);
        return;
    }
    Node Node_to_insert = newNode(x);
    Node prev_node = L->cursor->previous;
    Node_to_insert->next = L->cursor;
    Node_to_insert->previous = prev_node;
    L->cursor->previous = Node_to_insert;
    prev_node->next = Node_to_insert;
    (L->length) += 1;
    (L->index) += 1;
}

// Insert new element after cursor. Pre: length()>0, index()>=0.
void insertAfter(List L, int x){
    if ( L==NULL ){
        fprintf(stderr, "List Error: calling insertAfter() on NULL list.\n");
        exit(EXIT_FAILURE);
    }
    if ( L->cursor==NULL ){
        fprintf(stderr, "List Error: calling insertAfter() on a NULL cursor.\n");
        exit(EXIT_FAILURE);
    }
    if ( L->cursor==L->back ){
        append(L, x);
        return;
    }
    Node Node_to_insert = newNode(x);
    Node next_node = L->cursor->next;
    Node_to_insert->previous = L->cursor;
    Node_to_insert->next = next_node;
    L->cursor->next = Node_to_insert;
    next_node->previous = Node_to_insert;
    (L->length) += 1;
}

// Delete the front element. Pre: length()>0.
void deleteFront(List L){
    if ( L==NULL ){
        fprintf(stderr, "List Error: calling deleteFront() on NULL list.\n");
        exit(EXIT_FAILURE);
    }
    if ( L->front==NULL ){
        fprintf(stderr, "List Error: calling deleteFront() on empty list\n");
        exit(EXIT_FAILURE);
    }
    Node N = NULL;
    if( L->length==1 ){
      freeNode(&L->front);
      L->front = L->back = L->cursor = NULL;
      L->index = -1;
      L->length = 0;
   }
   else{
      N = L->front;
      L->front = L->front->next;
      freeNode(&N);
      L->front->previous = NULL;
      if( L->index==0 )
         L->cursor = NULL;
      L->index -= 1;
      L->length -= 1;
   }
}

// Delete the back element. Pre: length()>0.
void deleteBack(List L){
    if ( L==NULL ){
        fprintf(stderr, "List Error: calling deleteBack() on NULL list.\n");
        exit(EXIT_FAILURE);
    }
    if ( L->back==NULL )
    {
        fprintf(stderr, "List Error: calling deleteBack() on empty list\n");
        exit(EXIT_FAILURE);
    }
    Node N = NULL;
    if( L->length==1 ){
      freeNode(&L->front);
      L->front = L->back = L->cursor = NULL;
      L->index = -1;
      L->length = 0;
   }
   else{
      N = L->back;
      if( L->cursor==N ){
         L->cursor = NULL;
         L->index = -1;
      }
      L->back = L->back->previous;
      freeNode(&N);
      L->back->next = NULL;
      L->length--;
   }
}

// Delete cursor element, making cursor undefined. Pre: length()>0, index()>=0.
void delete(List L){
    if ( L==NULL ){
        fprintf(stderr, "List Error: calling delete() on NULL list.\n");
        exit(EXIT_FAILURE);
    }
    if ( L->cursor==NULL ){
        fprintf(stderr,"List Error: calling delete() on a NULL cursor.\n");
        exit(EXIT_FAILURE);
    }
    if ( L->cursor==L->front ){
      deleteFront(L);
      return;
    }
    if ( L->cursor==L->back ){
      deleteBack(L);
      return;
    }
   Node N=NULL;
   N = L->cursor;
   L->cursor = NULL;
   if( L->length==1 ){
      freeNode(&L->front);
      L->front = L->back = NULL;
   }
   else if( L->front==N ){
      N = L->front;
      L->front = L->front->next;
      freeNode(&N);
      L->front->previous = NULL;
   }
   else if( L->back==N ){
      N = L->back;
      L->back = L->back->previous;
      freeNode(&N);
      L->back->next = NULL;
   }
   else{
      N->previous->next = N->next;
      N->next->previous = N->previous;
      freeNode(&N);
   }
   L->length -= 1;
   L->index = -1;
}


// Other operations -----------------------------------------------------------
// Prints to the file pointed to by out, a string representation of L consisting
// of a space separated sequence of integers, with front on left.
void printList(FILE* out, List L){
    if ( L==NULL ){
        fprintf(stderr, "List Error: calling printList() on NULL list.\n");
        exit(EXIT_FAILURE);
    }
    if ( out==NULL ) {
        fprintf(stderr, "File Error: Unable to open file.\n");
        exit(EXIT_FAILURE);
    }
    moveFront(L);                                           
     while ( index(L)>=0 ){
        int current = get(L);
        fprintf(out, "%d ", current);
        moveNext(L);
    }
}

// Returns a new List representing the same integer sequence as L. The cursor in the
// new list is undefined, regardless of the state of the cursor in L. The state of L is unchanged.
List copyList(List L){
    if ( L==NULL ) {
        fprintf(stderr, "List Error: calling copyList() on NULL list.\n");
        exit(EXIT_FAILURE);
    }
    List listCopy = newList();
    Node nodeCopy = L->front;
    while ( nodeCopy!=NULL ){
        append(listCopy, nodeCopy->data);
        nodeCopy = nodeCopy->next;
    }
    return listCopy;
}