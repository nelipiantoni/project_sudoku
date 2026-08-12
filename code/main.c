#include <time.h>
#include "sudoku.h"


int main(void){
    int tab[9][9] = {0};

    srand(time(NULL));

    generate_tab(tab, 0, 0);
    print_tab(tab);
    
}

