// this implements bruteforce algorithm to find the greatest 
// clique in a graph (see graph.h and graph.c for graph representation)

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

// check if a vertex can be added to the clique
int is_clique(graph* g, int subset) {
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