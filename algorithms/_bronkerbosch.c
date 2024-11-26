#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../graph.h"  // Assuming graph.h defines the graph structure

// Helper function: Initialize an array with all vertices in the graph
void init_set(int* set, int size) {
    for (int i = 0; i < size; i++) {
        set[i] = i;  // Initialize with all vertices
    }
}

// Helper function: Check if a vertex is in a given set (P or X)
int in_set(int* set, int size, int v) {
    for (int i = 0; i < size; i++) {
        if (set[i] == v) {
            return 1;
        }
    }
    return 0;
}

// Helper function: Remove a vertex from a set
void remove_from_set(int* set, int* size, int v) {
    for (int i = 0; i < *size; i++) {
        if (set[i] == v) {
            // Shift the remaining elements to remove v
            for (int j = i; j < *size - 1; j++) {
                set[j] = set[j + 1];
            }
            (*size)--;  // Decrease the size of the set
            return;
        }
    }
}

// Helper function: Add a vertex to a set
void add_to_set(int* set, int* size, int v) {
    set[*size] = v;
    (*size)++;
}

// Bron-Kerbosch recursive function
void bron_kerbosch(
    int* R, int R_size, // Current clique R
    int* P, int P_size, // Potential vertices P
    int* X, int X_size, // Excluded vertices X
    graph* g,           // The graph
    int*** cliques,     // List of cliques found
    int* clique_count,  // Number of cliques found
    int* max_clique_size // Size of the largest clique
) {
    // Base case: If P and X are both empty, R is a maximal clique
    if (P_size == 0 && X_size == 0) {
        if (R_size > *max_clique_size) {
            *max_clique_size = R_size;
            *clique_count = 0;  // Reset cliques
        }

        if (R_size == *max_clique_size) {
            // Store the current clique (R)
            (*cliques) = realloc((*cliques), (*clique_count + 1) * sizeof(int*));
            (*cliques)[*clique_count] = malloc(R_size * sizeof(int));
            for (int i = 0; i < R_size; i++) {
                (*cliques)[*clique_count][i] = R[i];
            }
            (*clique_count)++;
        }
        return;
    }

    // Try each vertex in P and add it to the current clique (R)
    for (int i = 0; i < P_size; i++) {
        int v = P[i];

        // Create new sets for the recursive call
        int new_R[R_size + 1];  // New clique R
        memcpy(new_R, R, R_size * sizeof(int));
        new_R[R_size] = v;

        // Create new P and X sets by checking neighbors in the graph
        int new_P[P_size];
        int new_P_size = 0;
        int new_X[X_size];
        int new_X_size = 0;

        // Update P and X for the next recursive call
        for (int j = 0; j < P_size; j++) {
            if (g->matrix[v][P[j]]) {
                new_P[new_P_size++] = P[j];
            }
        }
        for (int j = 0; j < X_size; j++) {
            if (g->matrix[v][X[j]]) {
                new_X[new_X_size++] = X[j];
            }
        }

        // Recurse
        bron_kerbosch(new_R, R_size + 1, new_P, new_P_size, new_X, new_X_size, g, cliques, clique_count, max_clique_size);

        // Remove v from P and add it to X
        remove_from_set(P, &P_size, v);
        add_to_set(X, &X_size, v);
    }
}

// Function to find the largest clique using Bron-Kerbosch algorithm
void bron_kerbosch_clique(graph* g) {
    // Arrays to hold R, P, X sets
    int* R = malloc(0 * sizeof(int));  // Initially empty set for R
    int* P = malloc(g->size * sizeof(int));  // All vertices in P initially
    int* X = malloc(0 * sizeof(int));  // Initially empty set for X

    // Initialize the P set with all vertices
    init_set(P, g->size);

    // Variables to store the result
    int** cliques = NULL;
    int clique_count = 0;
    int max_clique_size = 0;

    // Start the Bron-Kerbosch algorithm
    bron_kerbosch(R, 0, P, g->size, X, 0, g, &cliques, &clique_count, &max_clique_size);

    // Print results
    printf("Largest cliques (size: %d):\n", max_clique_size);
    for (int i = 0; i < clique_count; i++) {
        printf("Clique %d: ", i + 1);
        for (int j = 0; j < max_clique_size; j++) {
            printf("%d ", cliques[i][j]);
        }
        printf("\n");
        free(cliques[i]);  // Free each stored clique
    }

    // Cleanup
    free(R);
    free(P);
    free(X);
    free(cliques);
}