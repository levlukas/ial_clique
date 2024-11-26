#ifndef BRONKERBOSCH_H
#define BRONKERBOSCH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../graph.h"

int* init_array(int size);

int* copy_array(const int* source, int size);

void bron_kerbosch_clique(graph* g);

void bron_kerbosch(
    int* R, int R_size,
    int* P, int P_size,
    int* X, int X_size,
    graph* g,
    int*** cliques, int* clique_count, int* max_clique_size);

#endif // BRONKERBOSCH_H