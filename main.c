#include "graph.h"
#include "algorithms/bruteforce.h"
#include "algorithms/backtracking.h"
#include "experiment.h"

int main() {
    // nacteni grafu ze souboru a nalezeni nejvetsi kliky
    int g_size;
    g_size = graph_read_size("graph.gh");
    graph* g = graph_init(g_size);
    if (graph_read(g, "graph.gh")) {
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

    // porovnani algoritmu pro hledani v grafu o libovolnem poctu vrcholu s hustotou 0.5
    printf("\n========================================");
    printf("\nComparing algorithms on random graphs:\n");
    int graph_size_inp;
    printf("Enter the size of the graph: ");
    scanf("%d", &graph_size_inp);
    printf("========================================\n");
    run_experiments(graph_size_inp, 0.5); 
    printf("\n========================================\n");

    // casove srovnani s vystupem do souboru .csv
    int time_comp_inp;
    printf("Do you want to run time comparison experiment? (1 = yes, 0 = no): ");
    scanf("%d", &time_comp_inp);
    if (time_comp_inp) {
        time_comparison_experiment();
    }

    return 0;
}