#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int size;
    int** matrix;
} graph;

graph* graph_init(int size);

void graph_delete(graph* g);

int graph_read_size(const char* filename);

int graph_read(graph* g, const char* filename);

int graph_write(graph* g, const char* filename);

void graph_print(graph* g);

#endif // GRAPH_H
