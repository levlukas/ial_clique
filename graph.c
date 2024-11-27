#include <stdio.h>
#include <stdlib.h>


// struktura reprezentujici graf
typedef struct {
    int size;
    int** matrix;
} graph;

/*
 * Funkce pro inicializaci grafu
 * Parametry:
 * - size: velikost grafu
 */
graph* graph_init(int size) {
    // alokace pameti pro graf
    graph* g = (graph*)malloc(sizeof(graph));
    if (g == NULL) {  // kontrola alokace pameti
        return NULL;
    }
    
    // nastaveni velikosti grafu
    g->size = size;

    // alokace pameti pro matici sousednosti grafu
    g->matrix = (int**)malloc(size * sizeof(int*));
    if (g->matrix == NULL) {  // kontrola alokace pameti
        free(g);
        return NULL;
    }

    // inicializace matice, vsechny prvky nastaveny na 0
    for (int i = 0; i < size; i++) {  // volani pro kazdy radek
        g->matrix[i] = (int*)calloc(size, sizeof(int)); // alokace pameti pro radek
        if (g->matrix[i] == NULL) {  // kontrola alokace pameti
            for (int j = 0; j < i; j++) {
                free(g->matrix[j]);
            }
            free(g->matrix);
            free(g);
            return NULL;
        }
    }
    return g;
}


/*
 * Funkce pro uvolneni pameti grafu
 * Parametry:
 * - g: ukazatel na graf
 */
void graph_delete(graph* g) {
    if (g == NULL) {  // kontrola ukazatele
        return; 
    }

    // uvolneni pameti pro matici 
    for (int i = 0; i < g->size; i++) {
        free(g->matrix[i]);
    }
    free(g->matrix);

    // uvolneni pameti pro graf
    free(g);
}

/*
 * Funkce pro nacteni velikosti grafu ze souboru.
 * Parametry:
 * - filename: nazev souboru 
 */
int graph_read_size(const char* filename) {
    int size;  // promenna, kterou funkce vraci

    // otevreni souboru
    FILE* file = fopen(filename, "r");
    if (file == NULL) {  // kontrola otevreni souboru
        fprintf(stderr, "Error: Could not open file '%s'\n", filename);
        return -1;  
    }

    // nacteni velikosti 
    if (fscanf(file, "%d", &size) != 1) {  // kontrola nacteni
        fprintf(stderr, "Error: Failed to read graph size from file\n");
        fclose(file);
        return -1; 
    }

    // kontrola velikosti (zda je to kladne cislo)
    if (size <= 0) {
        fprintf(stderr, "Error: Invalid graph size (%d) in file\n", size);
        fclose(file);
        return -1;  
    }

    fclose(file);
    return size;  
}

/*
 * Funkce pro nacteni grafu ze souboru.
 * Parametry:
 * - g: ukazatel na graf
 * - filename: nazev souboru 
 */
int graph_read(graph* g, const char* filename) {
    // otevreni souboru
    FILE* file = fopen(filename, "r");
    if (file == NULL) {  // kontrola otevreni souboru
        fprintf(stderr, "Error: Could not open file '%s'\n", filename);
        return 0;
    }

    // nacteni velikosti grafu
    int size;
    if (fscanf(file, "%d", &size) != 1) {  // kontrola nacteni
        fprintf(stderr, "Error: Failed to read graph size from file\n");
        fclose(file);
        return 0;
    }

    // kontrola velikosti grafu
    if (size != g->size) {
        fprintf(stderr, "Error: Graph size mismatch (expected %d, got %d)\n", g->size, size);
        fclose(file);
        return 0;
    }

    // cteni matice grafu
    for (int i = 0; i < size; i++) {  // cteni radku
        for (int j = 0; j < size; j++) {  // cteni prvku
            if (fscanf(file, "%d", &g->matrix[i][j]) != 1) {  // kontrola nacteni a zapis do matice
                fclose(file);
                return 0;
            }
        }
    }
    fclose(file);
    return 1;
}

/*
 * Funkce pro zapis grafu do souboru.
 * Parametry:
 * - g: ukazatel na graf
 * - filename: nazev souboru 
 */
int graph_write(graph* g, const char* filename) {
    // otevreni souboru
    FILE* file = fopen(filename, "w");
    if (file == NULL) {  // kontrola otevreni souboru
        return 0;
    }

    // zapis velikosti matice
    fprintf(file, "%d\n", g->size);

    // zapis samotne matice
    for (int i = 0; i < g->size; i++) {  // zapis radku
        for (int j = 0; j < g->size; j++) {  // zapis prvku
            fprintf(file, "%d ", g->matrix[i][j]);
        }
        fprintf(file, "\n");  // po radku symbol 'newline'
    }
    fclose(file);
    return 1;
}


/*
 * Funkce pro vypis grafu do terminalu.
 * Parametry:
 * - g: ukazatel na graf
 */
void graph_print(graph* g) {
    // vypis velikosti grafu
    printf("%d\n", g->size);

    // tisk matice
    for (int i = 0; i < g->size; i++) {  // vypis kazdeho radku
        for (int j = 0; j < g->size; j++) {  // vypis prvku
            printf("%d ", g->matrix[i][j]);
        }
        printf("\n");  // po radku symbol 'newline'
    }
}
