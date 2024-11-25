#ifndef BACKTRACKING_H
#define BACKTRACKING_H

#include <stdio.h>
#include <stdlib.h>
#include "../graph.h"

// Function to solve the clique problem using backtracking
void backtracking(graph* g);

int is_clique_backtracking(graph* g, int* clique, int clique_size, int vertex);

void find_clique_backtracking(graph* g, int* clique, int clique_size, int* max_size, int** solutions, int* solution_count, int vertex);

#endif // BACKTRACKING_H
