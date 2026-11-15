/*** 
* Peter Liang
* xliang41
* 2024 Fall CSE 101 PA1
* Lex.c
* Client module for List ADT. 
***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#define MAX_LEN 300

// Custom strdup function
char* mystrdup(const char* s){
    char* p = malloc(strlen(s) + 1);
    if (p) strcpy(p, s);
    return p;
}

// Function to remove newline character from a string
void clean(char* s){
    size_t len = strlen(s);
    if (len > 0 && s[len-1] == '\n') {
        s[len-1] = '\0';
    }
}

int main(int argc, char* argv[]) {
    int line_count = 0;
    FILE *in, *out;
    char line[MAX_LEN];

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

    // Count the number of lines in the input file
    while (fgets(line, MAX_LEN, in) != NULL) {
        line_count++;
    }

    // Allocate memory for the array of strings
    char** strArray = malloc(line_count * sizeof(char*));
    if (strArray == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(in);
        fclose(out);
        exit(1);
    }

    // Reset file pointer to beginning of file
    rewind(in);

    // Read lines into strArray
    for (int i = 0; i < line_count; i++) {
        if (fgets(line, MAX_LEN, in) == NULL) {
            fprintf(stderr, "Error reading line %d\n", i+1);
            fclose(in);
            fclose(out);
            for (int j = 0; j < i; j++) {
                free(strArray[j]);
            }
            free(strArray);
            exit(1);
        }
        clean(line);  // Remove newline character
        strArray[i] = mystrdup(line);
        if (strArray[i] == NULL) {
            fprintf(stderr, "Memory allocation failed for line %d\n", i+1);
            fclose(in);
            fclose(out);
            for (int j = 0; j < i; j++) {
                free(strArray[j]);
            }
            free(strArray);
            exit(1);
        }
    }

    // Create and populate the List
    List L = newList();
    append(L, 0);
    for (int i = 1; i < line_count; i++) {
        moveFront(L);
        while (index(L) >= 0) {
            if (strcmp(strArray[get(L)], strArray[i]) > 0) {
                insertBefore(L, i);
                break;
            }
            moveNext(L);
        }
        if (index(L) < 0) {
            append(L, i);
        }
    }

    // Write sorted lines to output file
    moveFront(L);
    while (index(L) >= 0) {
        int idx = get(L);
        fprintf(out, "%s\n", strArray[idx]);
        moveNext(L);
    }

    // Free allocated memory and close files
    freeList(&L);
    for (int i = 0; i < line_count; i++) {
        free(strArray[i]);
    }
    free(strArray);
    fclose(in);
    fclose(out);

    return 0;
}