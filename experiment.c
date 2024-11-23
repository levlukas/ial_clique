#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"
#include "bruteforce.h"
#include "backtracking.h"

// Generate a random graph of given size
graph* generate_random_graph(int size, double density) {
    graph* g = graph_init(size);

    // Allocate memory for the adjacency matrix
    for (int i = 0; i < size; i++) {
        g->matrix[i] = (int*)malloc(size * sizeof(int));
    }

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
void run_experiments(int graph_size, double density) {
    printf("Running experiments on random graphs (size: %d, density: %.2f)\n", graph_size, density);

    // Generate a random graph
    graph* g = generate_random_graph(graph_size, density);

    // Measure and print time for bruteforce
    printf("\nRunning bruteforce...\n");
    double time_bruteforce = measure_execution_time(bruteforce, g);
    printf("Bruteforce time: %.6f seconds\n", time_bruteforce);

    // Measure and print time for backtracking
    printf("\nRunning backtracking...\n");
    double time_backtracking = measure_execution_time(backtracking, g);
    printf("Backtracking time: %.6f seconds\n", time_backtracking);

    // Free the graph memory
    graph_delete(g);
}
