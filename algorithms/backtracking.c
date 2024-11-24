#include <stdio.h>
#include <stdlib.h>
#include "../graph.h"

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
 * - int** solutions: array of arrays of vertices that form the largest clique
 * - int* solution_count: number of arrays in solutions
 */
void find_clique(graph* g, int* clique, int clique_size, int* max_size, int** solutions, int* solution_count, int vertex) {
    // If the current clique is larger than the largest found so far
    if (clique_size > *max_size) {
        *max_size = clique_size;
        *solution_count = 0; // Reset previous solutions
    }
    if (clique_size == *max_size) {
        // Store the current clique
        solutions[*solution_count] = (int*)malloc(clique_size * sizeof(int));
        if (solutions[*solution_count] == NULL) {
            return; // memory allocation check
        }

        for (int i = 0; i < clique_size; i++) {
            solutions[*solution_count][i] = clique[i];
        }
        (*solution_count)++;
    }

    // Try adding vertices to the clique
    for (int i = vertex; i < g->size; i++) {
        if (is_clique_backtracking(g, clique, clique_size, i)) {
            clique[clique_size] = i;
            find_clique(g, clique, clique_size + 1, max_size, solutions, solution_count, i + 1);
        }
    }
}

// main function to solve the clique problem (stores all the 'global' variables)
void backtracking(graph* g) {
    int* clique = (int*)malloc(g->size * sizeof(int));
    if (clique == NULL) {
        return; // memory allocation check
    }
    int** solutions = (int**)malloc(g->size * sizeof(int*));
    if (solutions == NULL) {
        return; // memory allocation check
    }
    int solution_count = 0;
    int max_size = 0;

    find_clique(g, clique, 0, &max_size, solutions, &solution_count, 0);

    // Print all largest cliques
    printf("Largest cliques (size: %d):\n", max_size);
    for (int i = 0; i < solution_count; i++) {
        printf("Clique %d: ", i + 1);
        for (int j = 0; j < max_size; j++) {
            printf("%d ", solutions[i][j]);
        }
        printf("\n");
        free(solutions[i]);
    }

    // Free memory
    free(clique);
    free(solutions);
}