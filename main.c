#include "graph.h"
#include "bruteforce.h"
#include "backtracking.h"

int main() {
    // Read the graph from a file
    graph* g = graph_init(4);
    if (graph_read(g, "graph.txt")) {
        printf("Graph loaded:\n");
        graph_print(g);

        // Find the largest clique using brute force
        printf("\nFinding the largest clique using brute force...\n");
        bruteforce(g);

        // Find the largest clique using backtracking
        printf("\nFinding the largest clique using backtracking...\n");
        backtracking(g);
    } else {
        printf("Failed to load the graph.\n");
    }

    // Free memory
    graph_delete(g);
    return 0;
}
