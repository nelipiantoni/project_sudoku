#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "sudoku.h"


int main(void){
    int tab[9][9] = {0};
    int original[9][9] = {0};
    int solution[9][9] = {0};
    int difficulty;
    int target_removed;

    srand(time(NULL));
    
    printf("Izberi tezavnost:\n1 - Easy\n2 - Medium\n3 - Hard\n");
    if(scanf("%d", &difficulty) != 1){
        printf("Neveljaven vnos.\n");
        return 1;
    }
    
    if(difficulty == 1){
        target_removed = (rand() % 6) + 43;
    }else if(difficulty == 2){
        target_removed = (rand() % 7) + 49;
    }else if(difficulty == 3){
        target_removed = (rand() % 7) + 56;
    }else{
        printf("Napacno vstavljena vrednost. Tezavnost ne obstaja.\n");
        return 1;
    }

    clock_t start = clock();
    if(!generate_puzzle(tab, solution, target_removed)){
        printf("Sudokuja ni uspelo generirati.\n");
        return 1;
    }
    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Cas generiranja: %.3f sekund\n", elapsed);
    
    memcpy(original, tab, sizeof(original));

    play_sudoku(tab, original, solution);

    return 0;
}

