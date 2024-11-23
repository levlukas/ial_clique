#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

// check if adding a vertex forms a clique
int is_clique_backtracking(graph* g, int* clique, int clique_size, int vertex) {
    for (int i=0; i<clique_size; i++) {
        if (g->matrix[clique[i]][vertex] == 0) {  // if there is no edge at [i][vertex]
            return 0;  // not a clique
        }
    }
    return 1;  // great success
}

/* this is called from backtracking function where the variables for the function are initialized
 * this iterates through all vertices and if they can form a clique with the current clique, recuesion is called
 * parametr:
 * - graph* g: the graph
 * - int* clique: array of vertices in the current clique
 * - int clique_size: number of vertices currently in the clique
 * - int* max_clique: the largest clique found so far
 * - int* max_size: the size of the largest clique found so far
 * - int vertex: the vertex to be tested for inclusion in the clique.
 */
void find_clique(graph* g, int* clique, int clique_size, int* max_clique, int* max_size, int vertex) {
    // if the current clique is larger than the largest clique found so far
    if (clique_size > *max_size) {
        *max_size = clique_size;
        for (int i=0; i<clique_size; i++) {
            max_clique[i] = clique[i];
        }
    }

    // try adding vertices from the current vertex to the end of the graph
    for (int i=vertex; i<g->size; i++) {
        if (is_clique_backtracking(g, clique, clique_size, i)) {
            clique[clique_size] = i;
            find_clique(g, clique, clique_size+1, max_clique, max_size, i+1);
        }
    }
}

// main function to solve the clique problem (stores all the 'global' variables)
void backtracking(graph* g) {
    int* clique = (int*)malloc(g->size * sizeof(int));  // allocate memory for clique
    if (clique == NULL) {
        return; // memory allocation check
    }
    int* max_clique = (int*)malloc(g->size * sizeof(int));  // allocate memory for max_clique
    if (max_clique == NULL) {
        return; // memory allocation check
    }
    int max_size = 0;  // size of the largest clique found

    // start from the first vertex
    find_clique(g, clique, 0, max_clique, &max_size, 0);

    // print the largest clique found
    printf("Largest clique: ");
    printf("Size: %d, Vertices: ", max_size);
    for (int i=0; i<max_size; i++) {
        printf("%d ", max_clique[i]);
    }
    printf("\n");

    // free memory
    free(clique);
    free(max_clique);
}