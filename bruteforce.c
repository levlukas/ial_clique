// this implements bruteforce algorithm to find the greatest 
// clique in a graph (see graph.h and graph.c for graph representation)

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

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

// find the greatest clique in the graph
void bruteforce(graph* g) {
    int max_clique = 0;  // size of the largest clique found
    int max_subset = 0;  // subset representing the largest clique

    // iterate over all possible subsets of vertices
    int max_subset_size = 1 << g->size;  // 2^size -> binary shift
    for (int subset = 1; subset < max_subset_size; subset++) {  // iterate over all subset sizes
        if (is_clique_bruteforce(g, subset)) {
            // count number of vertices in the subset
            int count = 0;
            for (int i = 0; i < g->size; i++) {  // for each i in size
                if (subset & (1 << i)) {  // if i is in subset
                    count++;  // increment count
                }
            }

            // check if the subset is the largest clique found
            if (count > max_clique) {
                max_clique = count;
                max_subset = subset;
            }
        }
    }

    // print the largest clique found
    printf("Largest clique: ");
    printf("Size: %d, Vertices: ", max_clique);
    for (int i = 0; i < g->size; i++) {
        if (max_subset & (1 << i)) {
            printf("%d ", i);
        }
    }
    printf("\n");
}