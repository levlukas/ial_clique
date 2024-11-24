# Greates Clique Problem
- This project tries to compare multiple algorithms of finding the largest clique in a non-oriented graph.
  
## Summary
- This program should contain a way of I/O of the non-oriented graphs
- It should contain multiple algos for finding greatest clique
- It should compare time complexity of each algo experimentally to the theoretical complexity

## Algorithms
- `bruteforce.c` vytvoří všechny možné podgrafy a hledá v nich kliky, ty největší vrátí. Podgrafy vytváří díky bitové interpretaci těchto podgrafů, a tak je vše paměťově náročné. Algoritmus má pak problém s maticemi sousedů nad velikost 32.
- `smart_bruteforce.c` narozdíl od výše zmíněného používá pro interpretaci matice pole (array) o vhodné velikosti. Paměť pro každý z podgrafů alokuje dynamicky a uvolňuje ji, pokud je to vhodné.
- `backtracking.c`

## Zadani
Náhradní projekt je určen pouze pro studenty, kteří v předmětu IFJ neřeší souběžný projekt (např. studenti FEKT nebo studenti opakující předmět). Tento projekt je týmový a řeší jej trojice nebo čtveřice studentů.

Zadání varianty

Klika grafu je podgraf, který je úplným grafem (=kterýkoliv vrchol kliky je tedy spojen hranou se všemi ostatními vrcholy kliky).

Vytvořte program pro hledání největší kliky v neorientovaném grafu. Pokud existuje více řešení, nalezněte všechna. Výsledky prezentujte vhodným způsobem. Součástí projektu bude načítání grafů ze souboru a vhodné testovací grafy. V dokumentaci uveďte teoretickou složitost úlohy a porovnejte ji s experimentálními výsledky.

Všeobecné informace a pokyny k náhradním projektům

Řešení bude vypracováno v jazyce C a bude přeložitelné (pomocí příkazu make) na serveru eva.fit.vutbr.cz. Všechny zdrojové kódy, hlavičkové soubory, testovací data aj. budou logicky separovány a uloženy v příhodně pojmenovaných podadresářích. Použití nestandardních knihoven není dovoleno. Všechny části zadání varianty jsou nutnou součástí řešení.

Celkové hodnocení projektu sestává z následujících kategorií:

funkčnost implementace (až 6 bodů),
projektová dokumentace (až 4 body),
obhajoba (až 5 bodů).
Řešení zabalené v jediném ZIP archivu je odevzdáváno pouze vedoucím týmu prostřednictvím STUDISu. Závazné pokyny pro vypracování projektové dokumentace a doporučení pro závěrečné obhajoby naleznete v Moodlu v sekci Projekty.

