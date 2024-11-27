#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"

graph* generate_random_graph(int size, double density);

double measure_execution_time(void (*algorithm)(graph*), graph* g);

void run_experiments(int graph_size, double density);

void time_comparison_experiment();

#endif // EXPERIMENT_H