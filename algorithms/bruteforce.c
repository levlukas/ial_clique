// this implements bruteforce algorithm to find the greatest 
// clique in a graph (see graph.h and graph.c for graph representation)

#include <stdio.h>
#include <stdlib.h>
#include "../graph.h"

// check if a vertex can be added to the clique
int is_clique_bruteforce(graph* g, int subset) {
    for (int i = 0; i < g->size; i++) {
        for (int j = i + 1; j < g->size; j++) {
            // check if both vertices are in the subset
            if ((subset & (1 << i)) && (subset & (1 << j))) {
                // check if there is no edge between them
                if (g->matrix[i][j] == 0) {
                    return 0;
                }
            }
        }
    }
    return 1;  // great success
}


// Find all cliques of the largest size
void bruteforce(graph* g) {
    int max_clique_size = 0;  // Size of the largest clique found
    int max_subset_size = 1 << g->size;  // Total subsets: 2^size

    // Allocate memory to store all largest cliques
    int** largest_cliques = (int**)malloc(max_subset_size * sizeof(int*));
    int* clique_sizes = (int*)malloc(max_subset_size * sizeof(int));
    int clique_count = 0;

    for (int subset = 1; subset < max_subset_size; subset++) { // Iterate over all subsets
        if (is_clique_bruteforce(g, subset)) {
            // Count vertices in the subset
            int count = 0;
            for (int i = 0; i < g->size; i++) {
                if (subset & (1 << i)) {
                    count++;
                }
            }

            if (count > max_clique_size) {
                // New largest clique size: clear previous results
                max_clique_size = count;
                clique_count = 0;
                largest_cliques[clique_count] = (int*)malloc(g->size * sizeof(int));
                clique_sizes[clique_count] = 0;
                for (int i = 0; i < g->size; i++) {
                    if (subset & (1 << i)) {
                        largest_cliques[clique_count][clique_sizes[clique_count]++] = i;
                    }
                }
                clique_count++;
            } else if (count == max_clique_size) {
                // Add this clique to the results
                largest_cliques[clique_count] = (int*)malloc(g->size * sizeof(int));
                clique_sizes[clique_count] = 0;
                for (int i = 0; i < g->size; i++) {
                    if (subset & (1 << i)) {
                        largest_cliques[clique_count][clique_sizes[clique_count]++] = i;
                    }
                }
                clique_count++;
            }
        }
    }

    // Print all largest cliques
    printf("Largest cliques (size: %d):\n", max_clique_size);
    for (int i = 0; i < clique_count; i++) {
        printf("Clique %d: ", i + 1);
        for (int j = 0; j < clique_sizes[i]; j++) {
            printf("%d ", largest_cliques[i][j]);
        }
        printf("\n");
    }

    // Free memory
    for (int i = 0; i < clique_count; i++) {
        free(largest_cliques[i]);
    }
    free(largest_cliques);
    free(clique_sizes);
}