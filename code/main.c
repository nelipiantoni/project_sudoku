#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sudoku.h"


int main(void){
    int tab[9][9] = {0};

    srand(time(NULL));

    generate_tab(tab, 0, 0);

    printf("Polna tabela:\n");
    print_tab(tab);

    remove_value(tab);

    printf("\nSudoku uganka:\n");
    print_tab(tab);

    int count = 0;
    count_solutions(tab, 0, 0, &count);
    printf("\nStevilo resitev: %d\n", count);

    return 0;
}

