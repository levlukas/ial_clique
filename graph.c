#include <stdio.h>
#include <stdlib.h>
//#include "graph.h"

typedef struct {
    int size;
    int** matrix;
} graph;

// initializes graph with given size
graph* graph_init(int size) {
    // allocate memory for graph
    graph* g = (graph*)malloc(sizeof(graph));
    if (g == NULL) {  // memory allocation check
        return NULL;
    }
    
    // copy size
    g->size = size;

    // allocate memory for matrix
    g->matrix = (int**)malloc(size * sizeof(int*));
    if (g->matrix == NULL) {  // memory allocation check
        free(g);
        return NULL;
    }

    // Allocate memory for each row of the matrix and initialize to 0
    for (int i = 0; i < size; i++) {
        g->matrix[i] = (int*)calloc(size, sizeof(int)); // Allocate and set to 0
        if (g->matrix[i] == NULL) {
            // Clean up in case of failure
            for (int j = 0; j < i; j++) {
                free(g->matrix[j]);
            }
            free(g->matrix);
            free(g);
            return NULL;
        }
    }

    return g;
}


// deletes graph and frees memory
void graph_delete(graph* g) {
    if (g == NULL) {
        return;  // Avoid dereferencing a NULL pointer
    }

    // free memory for matrix
    for (int i = 0; i < g->size; i++) {
        free(g->matrix[i]);
    }
    free(g->matrix);

    // free memory for graph
    free(g);
}

// reads graph from file
int graph_read(graph* g, const char* filename) {
    // open file
    FILE* file = fopen(filename, "r");
    if (file == NULL) {  // file open check
        return 0;
    }

    // read size
    int size;
    if (fscanf(file, "%d", &size) != 1) {  // read check, TODO: check if size is valid
        fclose(file);
        return 0;
    }

    // check size
    if (size != g->size) {
        fclose(file);
        return 0;
    }

    // read matrix
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (fscanf(file, "%d", &g->matrix[i][j]) != 1) {  // read check
                fclose(file);
                return 0;
            }
        }
    }

    // close file, return great success - very nice 
    fclose(file);

    return 1;
}

// writes graph to file
int graph_write(graph* g, const char* filename) {
    // open file
    FILE* file = fopen(filename, "w");
    if (file == NULL) {  // file open check
        return 0;
    }

    // write size
    fprintf(file, "%d\n", g->size);

    // write matrix
    for (int i = 0; i < g->size; i++) {  // write each row
        for (int j = 0; j < g->size; j++) {  // write each element
            fprintf(file, "%d ", g->matrix[i][j]);
        }
        fprintf(file, "\n");  // new line
    }

    // close file, return great success - very nice
    fclose(file);

    return 1;
}


// prints graph to stdout
void graph_print(graph* g) {
    // print size
    printf("%d\n", g->size);

    // print matrix
    for (int i = 0; i < g->size; i++) {  // print each row
        for (int j = 0; j < g->size; j++) {  // print each element
            printf("%d ", g->matrix[i][j]);
        }
        printf("\n");  // new line
    }
}
