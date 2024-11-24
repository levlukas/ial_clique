/*
 * Abstrakt:
 * Tento soubor obsahuje optimalizaci pro metodu "pristup hrubou silou" zahrnutou v souboru
 * algorithms/bruteforce.c. Tato optimalizace je zalozena na rekurzi a vyhodnocuje pouze 
 * podmnoziny, ktere jsou podezrele z formovani kliky.
 * 
 * Slozitost:
 * - casova: O(2^n * n^2), kde n je pocet vrcholu grafu.
 *  - iterace pres vsechny podmnoziny vrcholu: O(2^n)
 *  - kontrola, zda je podmnozina klikou: O(n^2)
 * - prostorova: O(n), kde n je pocet vrcholu grafu. TODO: overit
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../graph.h"  // obsahuje definici struktury graph (graf)

// globalni promenne pro uchovani vysledku
int s_max_clique_size = 0;      // velikost nejvetsi dosavadne nalezene kliky
int** s_largest_cliques = NULL; // dynamicky alokovane pole ukazatelu na pole vrcholu formujicich nejvetsi kliky
int s_clique_count = 0;         // pocet nejvetsich klik

/*
 * Funkce pro zjisteni, zda je dana podmnozina vrcholu grafu klika.
 * Parametry:
 * - graph* g: ukazatel na strukturu grafu
 * - int* subset: pole vrcholu tvorici podmnozinu
 * - int size: velikost podmnoziny
 * Vraci:
 * - true, pokud je podmnozina klika
 * - false, pokud byla nalezena hrana s hodnotou 0 v matici (hrana neexistuje)
 */
bool s_is_clique(graph* g, int* subset, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (!g->matrix[subset[i]][subset[j]]) {
                return false;  // nejde o kliku
            }
        }
    }
    return true;  // vstupni podgraf je klika
}

/*
 * Rekurzivni funkce pro nalezeni vsech nejvetsich klik v grafu.
 * Parametry:
 * - graph* g: ukazatel na strukturu grafu
 * - int* subset: pole vrcholu tvorici podmnozinu
 * - int subset_size: velikost podmnoziny
 * - int start: index prvniho vrcholu pro dalsi podmnozinu
 */
void s_find_cliques_recursive(graph* g, int* subset, int subset_size, int start) {
    // Evaluate current subset as a clique
    if (s_is_clique(g, subset, subset_size)) {
        if (subset_size > s_max_clique_size) {
            // Found a larger clique: reset the results
            s_max_clique_size = subset_size;
            s_clique_count = 0;

            // Free previously stored cliques
            for (int i = 0; i < s_clique_count; i++) {
                free(s_largest_cliques[i]);
            }
            s_largest_cliques = realloc(s_largest_cliques, sizeof(int*));
        }
        if (subset_size == s_max_clique_size) {
            // Store the current clique
            s_largest_cliques = realloc(s_largest_cliques, (s_clique_count + 1) * sizeof(int*));
            s_largest_cliques[s_clique_count] = malloc(subset_size * sizeof(int));
            for (int i = 0; i < subset_size; i++) {
                s_largest_cliques[s_clique_count][i] = subset[i];
            }
            s_clique_count++;
        }
    }

    // Generate further subsets
    for (int i = start; i < g->size; i++) {
        subset[subset_size] = i;
        s_find_cliques_recursive(g, subset, subset_size + 1, i + 1);
    }
}

/*
 * Funkce pro nalezeni vsech nejvetsich klik v grafu pomoci metody pristupu hrubou silou.
 * Parametry:
 * - graph* g: ukazatel na strukturu grafu
 */
void s_bruteforce(graph* g) {
    // Allocate space for the subset
    int* subset = malloc(g->size * sizeof(int));

    // Reset global variables
    s_max_clique_size = 0;
    s_clique_count = 0;
    s_largest_cliques = NULL;

    // Start recursive subset generation
    s_find_cliques_recursive(g, subset, 0, 0);

    // Print results
    printf("Largest cliques (size %d):\n", s_max_clique_size);
    for (int i = 0; i < s_clique_count; i++) {
        printf("Clique %d: ", i + 1);
        for (int j = 0; j < s_max_clique_size; j++) {
            printf("%d ", s_largest_cliques[i][j]);
        }
        printf("\n");
        free(s_largest_cliques[i]);  // Free each stored clique
    }
    free(s_largest_cliques);  // Free the array of cliques
    free(subset);  // Free the subset array
}