#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void bruteforce(graph* g);

// Checks if a subset of vertices is a clique
int is_clique(graph* g, int subset);

#endif // BRUTEFORCE_H