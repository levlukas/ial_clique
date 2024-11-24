#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../graph.h"

// Globals to store all maximal cliques of the largest size
int bnb_max_clique_size = 0;  // Largest clique size found
int** bnb_largest_cliques = NULL;  // Array of largest cliques
int bnb_clique_count = 0;  // Number of largest cliques found

// Function to check if a set of vertices forms a clique
bool bnb_is_clique(graph* g, int* subset, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (!g->matrix[subset[i]][subset[j]]) {
                return false;
            }
        }
    }
    return true;
}

// Helper function to store a clique
void bnb_store_clique(int* subset, int size) {
    if (size > bnb_max_clique_size) {
        // Found a larger clique: reset results
        bnb_max_clique_size = size;
        bnb_clique_count = 0;

        // Free previously stored cliques
        for (int i = 0; i < bnb_clique_count; i++) {
            free(bnb_largest_cliques[i]);
        }
        bnb_largest_cliques = realloc(bnb_largest_cliques, sizeof(int*));
    }
    if (size == bnb_max_clique_size) {
        // Store the current clique
        bnb_largest_cliques = realloc(bnb_largest_cliques, (bnb_clique_count + 1) * sizeof(int*));
        bnb_largest_cliques[bnb_clique_count] = malloc(size * sizeof(int));
        for (int i = 0; i < size; i++) {
            bnb_largest_cliques[bnb_clique_count][i] = subset[i];
        }
        bnb_clique_count++;
    }
}

// Recursive Branch-and-Bound function
void bnb_branch_and_bound(graph* g, int* subset, int subset_size, int* candidates, int candidate_count) {
    if (candidate_count == 0) {
        // No more candidates, evaluate current subset
        if (bnb_is_clique(g, subset, subset_size)) {
            bnb_store_clique(subset, subset_size);
        }
        return;
    }

    for (int i = 0; i < candidate_count; i++) {
        // Select the current candidate
        int v = candidates[i];

        // Add to the subset
        subset[subset_size] = v;

        // Generate new candidate list
        int* new_candidates = malloc(candidate_count * sizeof(int));
        int new_count = 0;

        for (int j = i + 1; j < candidate_count; j++) {
            if (g->matrix[v][candidates[j]]) {
                new_candidates[new_count++] = candidates[j];
            }
        }

        // Recursively explore with the updated subset and candidate list
        bnb_branch_and_bound(g, subset, subset_size + 1, new_candidates, new_count);

        // Free dynamically allocated candidate list
        free(new_candidates);
    }
}

// Main function to find all largest cliques using Branch-and-Bound
void branch_and_bound(graph* g) {
    // Allocate memory for the subset and candidates
    int* subset = malloc(g->size * sizeof(int));
    int* candidates = malloc(g->size * sizeof(int));
    for (int i = 0; i < g->size; i++) {
        candidates[i] = i;
    }

    // Reset global variables
    bnb_max_clique_size = 0;
    bnb_clique_count = 0;
    bnb_largest_cliques = NULL;

    // Start the Branch-and-Bound recursion
    bnb_branch_and_bound(g, subset, 0, candidates, g->size);

    // Print results
    printf("Largest cliques (size %d):\n", bnb_max_clique_size);
    for (int i = 0; i < bnb_clique_count; i++) {
        printf("Clique %d: ", i + 1);
        for (int j = 0; j < bnb_max_clique_size; j++) {
            printf("%d ", bnb_largest_cliques[i][j]);
        }
        printf("\n");
        free(bnb_largest_cliques[i]);  // Free each stored clique
    }

    // Free memory
    free(bnb_largest_cliques);
    free(subset);
    free(candidates);
}
