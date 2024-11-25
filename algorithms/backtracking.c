#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
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

void find_clique_backtracking(graph* g, int* current_clique, int clique_size, int*** largest_cliques, int* max_size, int* clique_count, int start) {
    // If the current clique is larger than the max clique found so far
    if (clique_size > *max_size) {
        *max_size = clique_size;

        // Free previously stored cliques
        for (int i = 0; i < *clique_count; i++) {
            free((*largest_cliques)[i]);
        }
        free(*largest_cliques);

        // Allocate new space for largest cliques
        *largest_cliques = NULL;
        *clique_count = 0;
    }

    // If the current clique matches the max size, store it
    if (clique_size == *max_size) {
        *largest_cliques = realloc(*largest_cliques, (*clique_count + 1) * sizeof(int*));
        if (*largest_cliques == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(1);
        }

        (*largest_cliques)[*clique_count] = malloc(clique_size * sizeof(int));
        if ((*largest_cliques)[*clique_count] == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(1);
        }
        for (int i = 0; i < clique_size; i++) {
            (*largest_cliques)[*clique_count][i] = current_clique[i];
        }
        (*clique_count)++;
    }

    // Backtracking step: Try adding vertices to the current clique
    for (int i = start; i < g->size; i++) {
        // Check if adding vertex `i` forms a valid clique
        if (is_clique_backtracking(g, current_clique, clique_size, i)) {
            // Add vertex `i` to the current clique
            current_clique[clique_size] = i;

            // Recur with the updated clique
            find_clique_backtracking(g, current_clique, clique_size + 1, largest_cliques, max_size, clique_count, i + 1);

            // Backtrack: No explicit action needed because we overwrite `current_clique[clique_size]` on the next loop iteration
        }
    }
}



void backtracking(graph* g) {
    // Allocate memory for tracking current clique and storing results
    int* current_clique = (int*)malloc(g->size * sizeof(int));  // Holds vertices of the current clique
    int** largest_cliques = NULL;                               // Array of largest cliques
    int max_size = 0;                                           // Size of the largest clique found
    int clique_count = 0;                                       // Number of largest cliques found

    if (current_clique == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return;
    }

    // Call the backtracking function
    find_clique_backtracking(g, current_clique, 0, &largest_cliques, &max_size, &clique_count, 0);

    // Print results
    printf("Largest cliques (size: %d):\n", max_size);
    for (int i = 0; i < clique_count; i++) {
        printf("Clique %d: ", i + 1);
        for (int j = 0; j < max_size; j++) {
            printf("%d ", largest_cliques[i][j]);
        }
        printf("\n");
        free(largest_cliques[i]);  // Free each stored clique
    }

    // Free allocated memory
    free(largest_cliques);
    free(current_clique);
}

