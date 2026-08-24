#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sudoku.h"



// preveri ali lahko vrednost vstavimo na podano mesto
int check_value(int tab[9][9], int row, int col, int value){
    int start_row;
    int start_col;

    // preverja vrstico
    for(int i = 0; i < 9; i++){
        if(tab[row][i] == value){
            return 0;
        }
    }
    // preverja stolpec
    for(int i = 0; i < 9; i++){
        if(tab[i][col] == value){
            return 0;
        }
    }
    // doloci zacetno vrstico in stolpec pripadajocega 3x3 kvadrata
    if(row < 3){
        start_row = 0;
    } else if(row < 6){
        start_row = 3;
    } else{
        start_row = 6;
    }
    if(col < 3){
        start_col = 0;
    } else if(col < 6){
        start_col = 3;
    } else{
        start_col = 6;
    }

    // preverja pripadajoc 3x3 kvadrat
    for(int i = start_row; i < start_row + 3; i++){
        for(int j = start_col; j < start_col + 3; j++){
            if(tab[i][j] == value){
                return 0;
            }
        }
    }
    // vrednost lahko vstavimo na podano mesto
    return 1;
}

// generira polno sudoku tabelo z rekurzijo in backtrackingom
int generate_tab(int tab[9][9], int row, int col){

    // ce smo prisli cez zadnjo vrstico je tabela uspesno generirana
    if(row > 8){
        return 1;
    }

    int values[9] = {1,2,3,4,5,6,7,8,9};

    // nakljucno premesamo vrstni red vrednosti od 1 do 9
    for(int i = 8; i > 0; i--){
        int x = rand() % (i + 1);

        int y = values[i];
        values[i] = values[x];
        values[x] = y;
    }

    // poskusamo vrednosti v nakljucnem vrstnem redu
    for(int i = 0; i < 9; i++){
        int value = values[i];

        // preverimo ali lahko vrednost vstavimo na trenutno mesto
        if(check_value(tab, row, col, value)){

            // vstavimo vrednost v tabelo
            tab[row][col] = value;

            // rekurzivno nadaljujemo na naslednje mesto v tabeli
            if(col < 8){
                if(generate_tab(tab, row, col + 1)){
                    return 1;
                }
            } else{
                if(generate_tab(tab, row + 1, 0)){
                    return 1;
                }
            }
            // ce rekurzija vraca 0, izbrisemo neuspesen poizkus iz tabele
            tab[row][col] = 0;
        }
    }
    // ce ni mogoce vstaviti nobene veljavne vrednosti, izvedemo backtracking
    return 0;
}

//izpise sudoku tabelo v pregledni obliki
void print_tab(int tab[9][9]){

    for(int i = 0; i < 9; i++){
        // izpise vodoravno crto med 3x3 kvadrati
        if(i % 3 == 0){
            printf("+-------+-------+-------+\n");
        }

        for(int j = 0; j < 9; j++){
            if(j % 3 == 0){
                printf("| ");
            }
            if(tab[i][j] == 0){
                printf(". ");
            }else{
                printf("%d ", tab[i][j]);
            }
            if(j % 8 == 0 && j != 0){
                printf("|");
            }
        }
        printf("\n");
        if(i == 8){
            printf("+-------+-------+-------+\n");
        }
    }
}

// rekurzivno presteje resitve sudoku tabele do najvec dveh resitev
int count_solutions(int tab[9][9], int row, int col, int *count){

    // ko je tabela izpolnjena
    if(row > 8){
        // najdena je nova resitev zato povecamo stevec
        (*count)++;
        // ko najdemo drugo resitev prekinemo nadaljnje iskanje
        if(*count >= 2){
           return 1; 
        }
        // isce preostale resitve rekurzivno
        return 0;
    }

    // ce je mesto v tabeli prazno
    if(tab[row][col] == 0){
        // puskusamo vrednosti od 1 do 9 na to mesto
        for(int value = 1; value <= 9; value++){
            // preverimo ali lahko vrednost vstavimo na trenutno mesto
            if(check_value(tab, row, col, value)){
                tab[row][col] = value;
                // ce je bila najdena druga resitev, signal vrnemo skozi rekurzivne klice
                if(col < 8){
                    if(count_solutions(tab, row, col + 1, count)){
                        tab[row][col] = 0;
                        return 1;
                    }
                }else{
                    if(count_solutions(tab, row + 1, 0, count)){
                        tab[row][col] = 0;
                        return 1;
                    }
                }
            }
            tab[row][col] = 0;
        }
    }else{
        // ce mesto ni prazno, ga preskocimo in nadaljujemo na naslednje mesto
        if(col < 8){
            if(count_solutions(tab, row, col + 1, count)){
                return 1;
            }
        }else{
            if(count_solutions(tab, row + 1, 0, count)){
                return 1;
            }
        }
    }
    // vrnemo se na prejsnji rekurzivni klic in nadaljujemo iskanje
    return 0;
}

// odstranjuje vrednosti iz tabele, dokler ostane natanko ena resitev
int remove_values(int tab[9][9], int target_removed){
    // preveri, ali je zeleno stevilo odstranjenih mest v dovoljenem razponu
    if(target_removed < 1 || target_removed > 64){
        return 0;
    }

    int removed = 0;
    int positions[81];

    // ustvarimo seznam vseh 81 mest v tabeli
    for(int i = 0; i < 81; i++){
        positions[i] = i;
    }
    // nakljucno premesamo vrstni red mest za odstranjevanje
    for(int i = 80; i > 0; i--){
        int x = rand() % (i + 1);

        int y = positions[i];
        positions[i] = positions[x];
        positions[x] = y;
    }

    for(int i = 0; i < 81; i++){
        // indeks mesta pretvorimo v vrstico in stolpec
        int row = positions[i] / 9;
        int col = positions[i] % 9;
        // shranimo vrednost, da jo lahko vrnemo, ce odstranitev porusi enolicnost
        int old_value = tab[row][col];
        tab[row][col] = 0;
        int count = 0;
        
        count_solutions(tab, 0, 0, &count);

        // odstranitev obdrzimo samo ce ima tabela se vedno eno resitev
        if(count == 1){
            removed++;
        } else{
            tab[row][col] = old_value;
        }

        // ce smo dosegli zazeljeno stevilo odstranjenih mest
        if(target_removed == removed){
            return 1;
        }
    }
    // pregledali smo vsa mesta, vendar nismo dosegli cilja
    return 0;
}

// generira novo sudoku uganko in shrani njeno polno resitev
int generate_puzzle(int tab[9][9], int solution[9][9], int target_removed){
    int full_tab[9][9] = {0};
    int success = 0;
    int attempts = 0;
    int max_attempts = 150;
    // generiranje ponavljamo dokler ne dosezemo zazelenega
    // stevila odstranjenih mest ali maksimalnega stevila poskusov
    while(success == 0 && attempts < max_attempts){ 
        // pred novim poskusom pocistimo tabelo
        memset(tab, 0, sizeof(tab[0][0]) * 81);
       
        generate_tab(tab, 0, 0);
        // shranimo polno resitev, preden zacnemo odstranjevati vrednosti
        memcpy(full_tab, tab, sizeof(full_tab));

        success = remove_values(tab, target_removed);

        attempts++;
    }
    // generiranje ni uspelo v maksimalnem stevilu poskusov
    if(success == 0){
        return 0;
    }
    // uspesno generirano polno tabelo shranimo kot pravilno resitev
    memcpy(solution, full_tab, sizeof(full_tab));

    return 1;
}

// omogoca uporabniku resevanje sudokuja, dokler ni resitev pravilna
int play_sudoku(int tab[9][9], int original[9][9], int solution[9][9]){
    int row, col, value;

    while(1){
        print_tab(tab);

        // uporabnik vnese vrstico, stolpec in vrednost od 1 do 9
        printf("Vnesi indeks vrstice, stolpca in vrednosti.\n");
        if(scanf("%d %d %d", &row, &col, &value) != 3){
            // napacen format vnosa
            printf("Neveljaven vnos.\n");

            // pocistimo se preostanek napacnega vnosa iz stdin do konca vrstice
            int vnos = getchar();

            while(vnos != '\n' && vnos != EOF){
                vnos = getchar();
            }
            continue;
        }
        // preverimo veljavnost vnesenih vrednosti
        if(row < 10 && 0 < row && col < 10 && 0 < col && value < 10 && 0 < value){
            
            // pretvorimo uporabniski vnos 1-9 v indekse 0-8
            row = row - 1;
            col = col - 1;
            
            // spreminjamo lahko samo mesta, ki so bila v zacetni uganki prazna
            if(original[row][col] == 0){
                tab[row][col] = value;
            }else{
                printf("Zacetnih vrednosti ne smete spreminjati.\n");
            }
        }else{
            printf("Neveljavna vrednost.\n");
        }
        // ko je tabela zapolnjena preverimo, ali je resitev pravilna
        if(is_complete(tab)){
            if(check_solution(tab, solution)){
                printf("Cestitke, resitev je pravilna.\n");
                return 1;
            }else{
                printf("Resitev ni pravilna. Poskusi popraviti napake.\n");
            }
        }
    }
}

// preveri ali so vsa mesta v tabeli zapolnjena
int is_complete(int tab[9][9]){

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(tab[i][j] == 0){
                return 0;
            }
        }
    }
    return 1;
}

// preveri ali se uporabnikova tabela ujema s pravilno resitvijo
int check_solution(int tab[9][9], int solution[9][9]){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(tab[i][j] != solution[i][j]){
                return 0;
            }
        }
    }
    return 1;
}


