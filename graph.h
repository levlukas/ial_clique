#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

// Graph structure definition
typedef struct {
    int size;
    int** matrix;
} graph;

// Initializes a graph with the given size
graph* graph_init(int size);

// Deletes a graph and frees memory
void graph_delete(graph* g);

// Reads a graph size from a file
int graph_read_size(const char* filename);

// Reads a graph from a file
int graph_read(graph* g, const char* filename);

// Writes a graph to a file
int graph_write(graph* g, const char* filename);

// Prints the graph to stdout
void graph_print(graph* g);

#endif // GRAPH_H
