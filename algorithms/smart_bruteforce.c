#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../graph.h"

// Globals for tracking largest cliques
int max_clique_size = 0;
int** largest_cliques = NULL;
int clique_count = 0;

// Check if a subset is a clique
bool s_is_clique(graph* g, int* subset, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (!g->matrix[subset[i]][subset[j]]) {
                return false;  // Not a clique
            }
        }
    }
    return true;
}

// Recursive function to generate and evaluate subsets
void s_find_cliques_recursive(graph* g, int* subset, int subset_size, int start) {
    // Evaluate current subset as a clique
    if (s_is_clique(g, subset, subset_size)) {
        if (subset_size > max_clique_size) {
            // Found a larger clique: reset the results
            max_clique_size = subset_size;
            clique_count = 0;

            // Free previously stored cliques
            for (int i = 0; i < clique_count; i++) {
                free(largest_cliques[i]);
            }
            largest_cliques = realloc(largest_cliques, sizeof(int*));
        }
        if (subset_size == max_clique_size) {
            // Store the current clique
            largest_cliques = realloc(largest_cliques, (clique_count + 1) * sizeof(int*));
            largest_cliques[clique_count] = malloc(subset_size * sizeof(int));
            for (int i = 0; i < subset_size; i++) {
                largest_cliques[clique_count][i] = subset[i];
            }
            clique_count++;
        }
    }

    // Generate further subsets
    for (int i = start; i < g->size; i++) {
        subset[subset_size] = i;
        s_find_cliques_recursive(g, subset, subset_size + 1, i + 1);
    }
}

// Function to find all largest cliques using recursion
void s_bruteforce(graph* g) {
    // Allocate space for the subset
    int* subset = malloc(g->size * sizeof(int));

    // Reset global variables
    max_clique_size = 0;
    clique_count = 0;
    largest_cliques = NULL;

    // Start recursive subset generation
    s_find_cliques_recursive(g, subset, 0, 0);

    // Print results
    printf("Largest cliques (size %d):\n", max_clique_size);
    for (int i = 0; i < clique_count; i++) {
        printf("Clique %d: ", i + 1);
        for (int j = 0; j < max_clique_size; j++) {
            printf("%d ", largest_cliques[i][j]);
        }
        printf("\n");
        free(largest_cliques[i]);  // Free each stored clique
    }
    free(largest_cliques);  // Free the array of cliques
    free(subset);  // Free the subset array
}