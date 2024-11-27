/*
 * ============================================================
 * 
 * NÁHRADNÍ PROJEKT - 09. NEJVĚTŠÍ KLIKA V NEORIENTOVANÉM GRAFU
 * 
 * ============================================================
 * 
 * Popis:
 * Náhradní projekt je určen pouze pro studenty, kteří v předmětu
 * IFJ neřeší souběžný projekt (např. studenti FEKT nebo studenti
 * opakující předmět). Tento projekt je týmový a řeší jej trojice
 * nebo čtveřice studentů.
 *
 * Zadání varianty:
 * Klika grafu je podgraf, který je úplným grafem (=kterýkoliv
 * vrchol kliky je tedy spojen hranou se všemi ostatními vrcholy
 * kliky).
 * 
 * Vytvořte program pro hledání největší kliky v neorientovaném
 * grafu. Pokud existuje více řešení, nalezněte všechna. Výsledky
 * prezentujte vhodným způsobem. Součástí projektu bude načítání
 * grafů ze souboru a vhodné testovací grafy. V dokumentaci uveďte
 * teoretickou složitost úlohy a porovnejte ji s experimentálními
 * výsledky.
 * 
 * Všeobecné informace a pokyny k náhradním projektům:
 * Řešení bude vypracováno v jazyce C a bude přeložitelné (pomocí
 * příkazu make) na serveru eva.fit.vutbr.cz. Všechny zdrojové kódy,
 * hlavičkové soubory, testovací data aj. budou logicky separovány
 * a uloženy v příhodně pojmenovaných podadresářích. Použití
 * nestandardních knihoven není dovoleno. Všechny části zadání
 * varianty jsou nutnou součástí řešení.
 * 
 * Celkové hodnocení projektu sestává z následujících kategorií:
 * - funkčnost implementace (až 6 bodů),
 * - projektová dokumentace (až 4 body),
 * - obhajoba (až 5 bodů).
 * 
 * Řešení zabalené v jediném ZIP archivu je odevzdáváno pouze vedoucím
 * týmu prostřednictvím STUDISu. Závazné pokyny pro vypracování
 * projektové dokumentace a doporučení pro závěrečné obhajoby naleznete
 * v Moodlu v sekci Projekty.
 */

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