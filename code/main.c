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

    int success = remove_values(tab, 63);

    if(success){
        printf("\nSudoku uganka:\n");
        print_tab(tab);
    } else{
        printf("\nNi uspelo odstraniti zazelenega stevila vrednosti.\n");
    }

    return 0;
}

