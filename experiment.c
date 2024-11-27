#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"
#include "algorithms/bruteforce.h"
#include "algorithms/backtracking.h"

/*
 * Funkce pro generovani nahodneho grafu pro danou velikost a hustotu hran.
 * Hrany jsou generovany nahodne pomoci funkce rand().
 */
graph* generate_random_graph(int size, double density) {
    srand(time(NULL));  // inicializace generatoru nahodnych cisel
    graph* g = graph_init(size);

    // zaplneni inicializovane matice hranami podle rand()
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            // pridani hrany s pravdepodobnosti density
            int edge = ((double)rand() / RAND_MAX) < density ? 1 : 0;
            g->matrix[i][j] = edge;  // graf je symetricky podle hlavni diagonaly
            g->matrix[j][i] = edge;
        }
        g->matrix[i][i] = 0;  // uzel nemuze mit hranu sam na sebe
    }

    return g;
}

/*
 * Funkce pro mereni casu vykonavani algoritmu.
 */
double measure_execution_time(void (*algorithm)(graph*), graph* g) {
    clock_t start = clock();  // pocatecni cas
    algorithm(g);             // spusteni vybraneho algoritmu  
    clock_t end = clock();    // koncovy cas

    // vraceni rozdilu casu v sekundach
    return (double)(end - start) / CLOCKS_PER_SEC;
}

/*
 * Funkce pro spusteni experimentu na nahodnych grafech.
 * Pro dany graf dane velikosti a hustoty se spusti oba algoritmy a vypise se cas jejich vykonavani.
 */
void run_experiments(int size, double density) {
    printf("Running experiments on random graphs (size: %d, density: %.2f)\n\n", size, density);

    // generace nahodneho grafu
    graph* g = generate_random_graph(size, density);

    graph_print(g);

    // spusteni bruteforce algoritmu
    printf("Running bruteforce...\n");
    clock_t start = clock();
    bruteforce(g);
    clock_t end = clock();
    printf("Bruteforce time: %.6f seconds\n\n", (double)(end - start) / CLOCKS_PER_SEC);

    // spusteni backtracking algoritmu
    printf("Running backtracking...\n");
    start = clock();
    backtracking(g);
    end = clock();
    printf("Backtracking time: %.6f seconds\n\n", (double)(end - start) / CLOCKS_PER_SEC);

    // uvolneni pameti pro nahodny graf
    graph_delete(g);
}

/*
 * Experiment pro srovnani casove slozitosti algoritmu
 * Tato funkce provede nekolik experimentu podle zadani a vystupni data ulozi do souboru .csv
 */
void time_comparison_experiment() {
    // otevreni souboru pro zapis
    FILE* file = fopen("experiment.csv", "w");
    if (file == NULL) {  // kontrola otevreni souboru
        printf("Failed to open the file.\n");
        return;
    }

    // zapis hlavicky csv
    fprintf(file, "size,density,bruteforce,backtracking\n");

    // provedeni experimentu pro mnozinu grafu
    for (int size = 10; size <= 100; size += 1) {  // pro velikosti grafu
        for (double density = 0.1; density <= 1.0; density += 0.3) {  // pro hustoty grafu
            // generace nahodneho grafu
            graph* g = generate_random_graph(size, density);

            // bruteforce
            double bruteforce_time = measure_execution_time(bruteforce, g);

            // backtracking
            double backtracking_time = measure_execution_time(backtracking, g);

            // zapis vysledku do souboru
            fprintf(file, "%d,%.2f,%.6f,%.6f\n", size, density, bruteforce_time, backtracking_time);

            // uvolneni pameti pro kazdy z grafu
            graph_delete(g);
        }
    }
    fclose(file);
}
