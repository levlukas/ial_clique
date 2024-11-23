#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"
#include "algorithms/bruteforce.h"
#include "algorithms/backtracking.h"

// Generate a random graph of given size
graph* generate_random_graph(int size, double density) {
    graph* g = graph_init(size);

    // Populate the adjacency matrix with random edges
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            // Add an edge with the given density probability
            int edge = (rand() / (double)RAND_MAX) < density ? 1 : 0;
            g->matrix[i][j] = g->matrix[j][i] = edge;
        }
        g->matrix[i][i] = 0;  // No self-loops
    }

    return g;
}

// Measure execution time of a function
double measure_execution_time(void (*algorithm)(graph*), graph* g) {
    clock_t start = clock();  // Start the timer
    algorithm(g);            // Run the algorithm
    clock_t end = clock();    // End the timer

    // Calculate the elapsed time in seconds
    return (double)(end - start) / CLOCKS_PER_SEC;
}

// Run experiments and compare algorithms
void run_experiments(int size, float density) {
    printf("Running experiments on random graphs (size: %d, density: %.2f)\n\n", size, density);

    // Generate a random graph
    graph* g = generate_random_graph(size, density);

    // Run bruteforce
    printf("Running bruteforce...\n");
    clock_t start = clock();
    bruteforce(g);
    clock_t end = clock();
    printf("Bruteforce time: %.6f seconds\n\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Run backtracking
    printf("Running backtracking...\n");
    start = clock();
    backtracking(g);
    end = clock();
    printf("Backtracking time: %.6f seconds\n\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Free the graph
    graph_delete(g);
}