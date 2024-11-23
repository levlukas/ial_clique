#include "graph.h"
#include "bruteforce.h"

int main() {
    // Read the graph from a file
    graph* g = graph_init(4);
    if (graph_read(g, "graph.txt")) {
        printf("Graph loaded:\n");
        graph_print(g);

        // Find the largest clique
        printf("\nFinding the largest clique...\n");
        bruteforce(g);
    } else {
        printf("Failed to load the graph.\n");
    }

    // Free memory
    graph_delete(g);
    return 0;
}
