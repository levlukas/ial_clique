#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../graph.h"

/*
 * Tato funkce kontroluje, zda pridani vrcholu (vertex) do podgrafu zachova tento
 * podgraf jako kliku.
 * Parametry:
 * - graph* g: ukazatel na strukturu grafu
 * - int* clique: pole vrcholu tvoricich kliku
 * - int clique_size: velikost kliky
 * - int vertex: pridavany vrchol
 */
int is_clique_backtracking(graph* g, int* clique, int clique_size, int vertex) {
    for (int i=0; i<clique_size; i++) {
        if (g->matrix[clique[i]][vertex] == 0) {  // pokud vrchol neni spojen s vrcholem 'vertex'
            return 0;  // nejedna se o kliku
        }
    }
    return 1;  // jedna se o kliku
}


/*
 * Rekurzivni funkce, ktera zahrnuje zpetne vyhledavani.
 * Parametry:
 * - graph* g: ukazatel na strukturu grafu
 * - int* current_clique: pole vrcholu tvoricich aktualni kliku
 * - int clique_size: velikost kliky
 * - int*** largest_cliques: pole ukazatelu na pole vrcholu tvoricich nejvetsi kliky
 * - int* max_size: velikost nejvetsi kliky
 * - int* clique_count: pocitadlo nejvetsich klik
 * - int start: index prvniho vrcholu pro dalsi podmnozinu
 */
void find_clique_backtracking(graph* g, int* current_clique, int clique_size, int*** largest_cliques, int* max_size, int* clique_count, int start) {
    // aktualizace nejvetsi nalezene kliky
    if (clique_size > *max_size) {
        *max_size = clique_size;

        // uvolneni pameti pro predchozi nejvetsi kliky
        for (int i = 0; i < *clique_count; i++) {
            free((*largest_cliques)[i]);
        }
        free(*largest_cliques);

        // obnoveni promennych
        *largest_cliques = NULL;
        *clique_count = 0;
    }

    // ulozi aktualni kliku, pokud se velikosti shoduje s nejvetsimi nalezenymi
    if (clique_size == *max_size) {
        *largest_cliques = realloc(*largest_cliques, (*clique_count + 1) * sizeof(int*));
        if (*largest_cliques == NULL) {  // kontrola alokace
            fprintf(stderr, "Memory allocation failed.\n");
            exit(1);
        }

        (*largest_cliques)[*clique_count] = malloc(clique_size * sizeof(int));
        if ((*largest_cliques)[*clique_count] == NULL) {  // kontrola alokace
            fprintf(stderr, "Memory allocation failed.\n");
            exit(1);
        }
        for (int i = 0; i < clique_size; i++) {  // kopirovani vrcholu do nejvetsi kliky
            (*largest_cliques)[*clique_count][i] = current_clique[i];
        }
        (*clique_count)++;  // inkrementace pocitadla
    }

    // zpetne vyhledavani
    for (int i = start; i < g->size; i++) {
        // zkontroluj pridani vrcholu 'i'
        if (is_clique_backtracking(g, current_clique, clique_size, i)) {
            current_clique[clique_size] = i;

            // pokud vytvori podmnozina s i kliku, potom zavolej rekurzivne pro start = i + 1, coz je dalsi vrchol, ktery se muze pridat
            find_clique_backtracking(g, current_clique, clique_size + 1, largest_cliques, max_size, clique_count, i + 1);
        }
        // pokud podminka neplati, potom se vetev od i dal nerozsiruje, ale namisto toho se rekurze vynori
    }
}


/*
 * Hlavni funkce pro algoritmus zpetneho vyhledavani.
 * Parametry:
 * - graph* g: ukazatel na strukturu grafu
 */
void backtracking(graph* g) {
    // alokace pameti pro aktualni kliku
    int* current_clique = (int*)malloc(g->size * sizeof(int));  // pole vrcholu tvoricich aktualni kliku
    int** largest_cliques = NULL;                               // pole ukazatelu na pole vrcholu tvoricich nejvetsi kliky
    int max_size = 0;                                           // velikost nejvetsi kliky
    int clique_count = 0;                                       // pocitadlo nejvetsich klik

    if (current_clique == NULL) {  // kontrola alokace
        fprintf(stderr, "Memory allocation failed.\n");
        return;
    }

    // zavolej rekurzivni funkci pro zpetne vyhledavani (provadi zpetne vyhledavani) a manipuluje s promennymi definovanymi vyse
    find_clique_backtracking(g, current_clique, 0, &largest_cliques, &max_size, &clique_count, 0);

    // tisk vysledku
    printf("Largest cliques (size: %d):\n", max_size);
    for (int i = 0; i < clique_count; i++) {
        printf("Clique %d: ", i + 1);
        for (int j = 0; j < max_size; j++) {
            printf("%d ", largest_cliques[i][j]);
        }
        printf("\n");
        free(largest_cliques[i]);  // uvolneni pameti pro pole vrcholu
    }

    // uvolneni pameti
    free(largest_cliques);
    free(current_clique);
}

