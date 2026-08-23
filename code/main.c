#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sudoku.h"


int main(void){
    int tab[9][9] = {0};

    srand(time(NULL));

    generate_puzzle(tab, 55);

    return 0;

}

