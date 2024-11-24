/*
 * Abstrakt:
 * Tento soubor obsahuje implementaci algoritmu "pristup hrubou silou"
 * (angl. bruteforce) pro hledání největších klik v grafu. 
 * Algoritmus vyzkousi vsechny mozne podmnoziny vrcholu grafu a zjisti,
 * zda se jedná o kliku. Pokud ano, overi, zda je tato kliku největší.
 * Vraci vsechny nejvetsi kliky v grafu.
 * 
 * Slozitost:
 * - casova: O(2^n * n^2), kde n je pocet vrcholu grafu.
 *  - iterace pres vsechny podmnoziny vrcholu: O(2^n)
 *  - kontrola, zda je podmnozina klikou: O(n^2)
 * - prostorova: O(2^n * n), kde n je pocet vrcholu grafu.  TODO: overit
 *  - pro kazdy vrchol (2^n) uchovavame jeho pritomnost v podmnozine (n)
 */

#include <stdio.h>
#include <stdlib.h>
#include "../graph.h"  // obsahuje definici struktury graph (graf)

/*
 * Tato funkce kontroluje, zda je dana podmnozina vrcholu grafu klika.
 * Parametry:
 * - graph* g: ukazatel na strukturu grafu
 * - int subset: reprezentace podmnoziny vrcholu (ve dvojkove soustave)
 * Vraci:
 * - 1, pokud je podmnozina klika
 * - 0, pokud byla nalezena hrana s hodnotou 0 v bitovem vektoru (hrana neexistuje)
 */
int is_clique_bruteforce(graph* g, int subset) {
    for (int i = 0; i < g->size; i++) {  // iteruje skrz kazdy prvek (i, j) v matici g
        for (int j = i + 1; j < g->size; j++) {  // podminka j > i, pro zadne duplikaty
            // i a j jsou souradnice vrcholu, kdyz provedu s jednickou binarni posun vlevo
            // o hodnotz i a j, pak dostanu masky vrcholu.
            // Po provedeni binarni konjunkce masky podgrafu (take binarni) s maskou
            // jednotlivych vrcholu a obe operaci vrati hodnotu pravda, pak oba tyto
            // vrcholy nalezi podgrafu 'subset'.
            if ((subset & (1 << i)) && (subset & (1 << j))) {
                // kontrola, zda mezi vybranymi vrcholy podgrafu je hrana
                if (g->matrix[i][j] == 0) {
                    return 0;  // mezi vrcholy neni hrana -> nejde o kompletni graf
                }
            }
        }
    }
    return 1;  // jde o kompletni podgraf, tedy kliku
}


/*
 * Hleda vsechny nejvetsi kliky v grafu pomoci metody pristupu hrubou silou.
 * Parametry:
 * - graph* g
 */
void bruteforce(graph* g) {
    int max_clique_size = 0;  // velikost nejvetsi dosavadne nalezene kliky
    int max_subset_size = 1 << g->size;  // pocet vsech moznych podgrafu (2^(g->size))

    // alokace pameti pro vsechny nejvetsi kliky
    // large_cliques je pole ukazatelu na pole vrcholu formujicich nejvetsi kliky
    int** largest_cliques = (int**)malloc(max_subset_size * sizeof(int*));
    if (largest_cliques == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    // pole pro uchovani velikosti kliky
    int* clique_sizes = (int*)malloc(max_subset_size * sizeof(int));
    if (clique_sizes == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    // pocet nejvetsich klik
    int clique_count = 0;

    // iterace skrz vsechny podmnoziny
    // subset se zde chova jako bitova maska (napr. 0b1010 -> vrcholy 1 a 3)
    for (int subset = 1; subset < max_subset_size; subset++) {  
        if (is_clique_bruteforce(g, subset)) {  // pokud je podmnozina klikou
            // zjisteni poctu vrcholu v podmnozine
            int count = 0;
            for (int i = 0; i < g->size; i++) {
                if (subset & (1 << i)) {
                    count++;
                }
            }

            if (count > max_clique_size) {  // pokud je aktualni klika vetsi nez dosavadni nejvetsi
                max_clique_size = count;

                for (int i = 0; i < clique_count; i++) {  // uvolneni pameti pro predchozi nejvetsi kliky
                    free(largest_cliques[i]);
                }
                clique_count = 0;
                largest_cliques[clique_count] = (int*)malloc(g->size * sizeof(int));  // alokace pameti pro novou kliku (jeji vrcholy)
                if (largest_cliques[clique_count] == NULL) {
                    fprintf(stderr, "Memory allocation failed.\n");
                    exit(1);
                }
                clique_sizes[clique_count] = 0;
                for (int i = 0; i < g->size; i++) {
                    if (subset & (1 << i)) {
                        largest_cliques[clique_count][clique_sizes[clique_count]++] = i;
                    }
                }
                clique_count++;
            } else if (count == max_clique_size) {  // pokud je aktualni klika stejne velka jako dosavadni nejvetsi
                largest_cliques[clique_count] = (int*)malloc(g->size * sizeof(int));  // alokace pameti pro novou kliku (jeji vrcholy)
                if (largest_cliques[clique_count] == NULL) {
                    fprintf(stderr, "Memory allocation failed.\n");
                    exit(1);
                }
                clique_sizes[clique_count] = 0;
                for (int i = 0; i < g->size; i++) {
                    if (subset & (1 << i)) {
                        largest_cliques[clique_count][clique_sizes[clique_count]++] = i;
                    }
                }
                clique_count++;
            }
        }
    }

    // vypis vysledku
    printf("Largest cliques (size: %d):\n", max_clique_size);
    for (int i = 0; i < clique_count; i++) {
        printf("Clique %d: ", i + 1);
        for (int j = 0; j < clique_sizes[i]; j++) {
            printf("%d ", largest_cliques[i][j]);
        }
        printf("\n");
    }

    // uvolneni pameti
    for (int i = 0; i < clique_count; i++) {
        free(largest_cliques[i]);
    }
    free(largest_cliques);
    free(clique_sizes);
}