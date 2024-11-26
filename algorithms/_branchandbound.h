#ifndef BRANCHANDBOUND_H
#define BRANCHANDBOUND_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../graph.h"

void bnb_branch_and_bound(graph* g, int* subset, int subset_size, int* candidates, int candidate_count);

void bnb_store_clique(int* subset, int size);

bool bnb_is_clique(graph* g, int* subset, int size);

void branch_and_bound(graph* g);

#endif // BRANCHANDBOUND_H