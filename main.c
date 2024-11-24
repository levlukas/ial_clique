#include "graph.h"
#include "algorithms/bruteforce.h"
#include "algorithms/backtracking.h"
#include "experiment.h"

int main() {
    // Example 1: Read a graph from a file and run algorithms
    int g_size;
    g_size = graph_read_size("graph.txt");
    graph* g = graph_init(g_size);
    if (graph_read(g, "graph.txt")) {
        printf("Graph loaded:\n");
        graph_print(g);

        printf("\nFinding the largest clique using bruteforce...\n");
        bruteforce(g);

        printf("\nFinding the largest clique using backtracking...\n");
        backtracking(g);
    } else {
        printf("Failed to load the graph.\n");
    }
    graph_delete(g);

    // Example 2: Compare time complexity with random graphs
    printf("\n========================================");
    printf("\nComparing algorithms on random graphs:\n");
    printf("========================================\n");
    run_experiments(10, 0.5);  // 10 vertices, 50% edge density
    printf("\n========================================\n");
    run_experiments(20, 0.5);  // 10 vertices, 50% edge density
    printf("\n========================================\n");
    run_experiments(50, 0.5);  // 10 vertices, 50% edge density - this is already failing for bruteforce
    printf("\n========================================\n");

    return 0;
}
