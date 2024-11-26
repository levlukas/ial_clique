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
 * Funkce pro uvolneni pameti alokovane pro nejvetsi kliky.
 */
void s_free_largest_cliques() {  // tato funkce je problematicka - double free
    if (s_largest_cliques != NULL) {
        for (int i = 0; i < s_clique_count; i++) {
            free(s_largest_cliques[i]);
        }
        free(s_largest_cliques);
        s_largest_cliques = NULL;
        s_clique_count = 0;
    }
}


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
    // kontrola, zda je aktualni podmnozina klika
    if (s_is_clique(g, subset, subset_size)) {
        if (subset_size > s_max_clique_size) {  // nalezena vetsi klika
            // vetsi klika byla nalezena -> aktualizace globalnich promennych
            s_free_largest_cliques();
            s_max_clique_size = subset_size;

            // uvolneni predchozich nejvetsich klik
            for (int i = 0; i < s_clique_count; i++) {
                free(s_largest_cliques[i]);
            }
            s_largest_cliques = realloc(s_largest_cliques, sizeof(int*));
            if (s_largest_cliques == NULL) {  // kontrola alokace
                fprintf(stderr, "Memory allocation failed.\n");
                return;
            }
        }
        if (subset_size == s_max_clique_size) {  // nalezena klika s aktualni maximalni velikosti
            // alokace pameti pro novou nejvetsi kliku a aktualizace globalnich promennych
            s_largest_cliques = realloc(s_largest_cliques, (s_clique_count + 1) * sizeof(int*));
            if (s_largest_cliques == NULL) {  // kontrola alokace
                fprintf(stderr, "Memory allocation failed.\n");
                return;
            }
            s_largest_cliques[s_clique_count] = malloc(subset_size * sizeof(int));
            if (s_largest_cliques[s_clique_count] == NULL) {  // kontrola alokace
                fprintf(stderr, "Memory allocation failed.\n");
                return;
            }
            for (int i = 0; i < subset_size; i++) {
                s_largest_cliques[s_clique_count][i] = subset[i];
            }
            s_clique_count++;
        }
    }

    // rekurzivni volani pro vsechny dalsi vrcholy
    for (int i = start; i < g->size; i++) {
        subset[subset_size] = i;
        s_find_cliques_recursive(g, subset, subset_size + 1, i + 1);
    }
}

/*
 * Funkce pro nalezeni vsech nejvetsich klik v grafu pomoci metody pristupu hrubou silou.
 * Spravuje globalni promenne pro urceni vysledku (ty jsou vyuzivany dilcimi funkcemi).
 * Vyvola rekurzivni vytvareni podmnozin a jejich vyhodnoceni.
 * Parametry:
 * - graph* g: ukazatel na strukturu grafu
 */
void s_bruteforce(graph* g) {
    // alokace pameti pro pole vrcholu tvoricich podmnozinu 
    int* subset = malloc(g->size * sizeof(int));
    if (subset == NULL) {  // kontrola alokace
        fprintf(stderr, "Memory allocation failed.\n");
        return;
    }

    // obnova globalnich promennych
    s_free_largest_cliques();
    s_max_clique_size = 0;

    // rekurzivni vyhodnoceni podmnozin
    s_find_cliques_recursive(g, subset, 0, 0);

    // tisk vysledku
    printf("Largest cliques (size %d):\n", s_max_clique_size);
    for (int i = 0; i < s_clique_count; i++) {
        printf("Clique %d: ", i + 1);
        for (int j = 0; j < s_max_clique_size; j++) {
            printf("%d ", s_largest_cliques[i][j]);
        }
        printf("\n");
        free(s_largest_cliques[i]);  // uvolneni pameti pro pole vrcholu
    }
    free(s_largest_cliques);  // uvolneni pameti pro pole ukazatelu
    free(subset);  // uvolneni pameti pro pole vrcholu
}