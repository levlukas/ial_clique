#ifndef SMART_BRUTEFORCE_H
#define SMART_BRUTEFORCE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../graph.h"

void s_free_largest_cliques();

bool s_is_clique(graph* g, int* subset, int size);

void s_find_cliques_recursive(graph* g, int* subset, int subset_size, int start, int depth);

void s_bruteforce(graph* g);

#endif // SMART_BRUTEFORCE_H