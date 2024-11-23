#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"

// Generate a random graph of given size
graph* generate_random_graph(int size, double density);

// Measure execution time of a function
double measure_execution_time(void (*algorithm)(graph*), graph* g);

// Run experiments and compare algorithms
void run_experiments(int graph_size, double density);

#endif // EXPERIMENT_H