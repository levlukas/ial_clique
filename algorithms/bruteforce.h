#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include <stdio.h>
#include <stdlib.h>
#include "../graph.h"

void bruteforce(graph* g);

int is_clique_bruteforce(graph* g, int subset);

#endif // BRUTEFORCE_H