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
    start_row = (row / 3) * 3;
    start_col = (col / 3) * 3;

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

// zamenja dve vrstici v sudoku tabeli
void swap_rows(int tab[9][9], int row1, int row2){

    // zamenjamo vrednosti v posameznih stolpcih obeh vrstic
    for(int j = 0; j < 9; j++){
        int temp = tab[row1][j];
        tab[row1][j] = tab[row2][j];
        tab[row2][j] = temp;
    }
}


// zamenja dva stolpca v sudoku tabeli
void swap_columns(int tab[9][9], int col1, int col2){

    // zamenjamo vrednosti v posameznih vrsticah obeh stolpcev
    for(int i = 0; i < 9; i++){
        int temp = tab[i][col1];
        tab[i][col1] = tab[i][col2];
        tab[i][col2] = temp;
    }
}

// zamenja dve skupini treh vrstic v sudoku tabeli
void swap_row_groups(int tab[9][9], int group1, int group2){

    // zamenjamo vse tri vrstice obeh skupin
    for(int i = 0; i < 3; i++){
        swap_rows(tab, group1 * 3 + i, group2 * 3 + i);
    }
}

// zamenja dve skupini treh stolpcev v sudoku tabeli
void swap_column_groups(int tab[9][9], int group1, int group2){

    // zamenjamo vse tri stolpce obeh skupin
    for(int i = 0; i < 3; i++){
        swap_columns(tab, group1 * 3 + i, group2 * 3 + i);
    }
}

// zamenja dve vrednosti v celotni sudoku tabeli
void swap_values(int tab[9][9], int value1, int value2){

    // zamenjamo vse pojavitve obeh vrednosti v tabeli
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(tab[i][j] == value1){
                tab[i][j] = value2;
            }else if(tab[i][j] == value2){
                tab[i][j] = value1;
            }
        }
    }
}

// ustvari zacetno veljavno sudoku tabelo
void create_base_tab(int tab[9][9]){

    int base_tab[9][9] = {
        {1,2,3,4,5,6,7,8,9},
        {4,5,6,7,8,9,1,2,3},
        {7,8,9,1,2,3,4,5,6},
        {2,3,4,5,6,7,8,9,1},
        {5,6,7,8,9,1,2,3,4},
        {8,9,1,2,3,4,5,6,7},
        {3,4,5,6,7,8,9,1,2},
        {6,7,8,9,1,2,3,4,5},
        {9,1,2,3,4,5,6,7,8}
    };

    // kopiramo zacetno tabelo v podano tabelo
    memcpy(tab, base_tab, sizeof(base_tab));
}

// nakljucno premesa veljavno sudoku tabelo z dovoljenimi zamenjavami
void randomize_tab(int tab[9][9]){

    int group1;
    int group2;
    int row1;
    int row2;
    int col1;
    int col2;
    int value1;
    int value2;

    // nakljucno zamenjamo vrstici znotraj iste skupine treh vrstic
    for(int i = 0; i < 10; i++){
        group1 = rand() % 3;
        row1 = group1 * 3 + rand() % 3;
        row2 = group1 * 3 + rand() % 3;

        while(row1 == row2){
            row2 = group1 * 3 + rand() % 3;
        }

        swap_rows(tab, row1, row2);
    }

    // nakljucno zamenjamo stolpca znotraj iste skupine treh stolpcev
    for(int i = 0; i < 10; i++){
        group1 = rand() % 3;
        col1 = group1 * 3 + rand() % 3;
        col2 = group1 * 3 + rand() % 3;

        while(col1 == col2){
            col2 = group1 * 3 + rand() % 3;
        }

        swap_columns(tab, col1, col2);
    }

    // nakljucno zamenjamo skupine treh vrstic
    group1 = rand() % 3;
    group2 = (group1 + 1 + rand() % 2) % 3;

    swap_row_groups(tab, group1, group2);

    // nakljucno zamenjamo skupine treh stolpcev
    group1 = rand() % 3;
    group2 = (group1 + 1 + rand() % 2) % 3;

    swap_column_groups(tab, group1, group2);

    // nakljucno zamenjamo oznaki dveh stevilk
    value1 = (rand() % 9) + 1;
    value2 = (value1 + rand() % 8) % 9 + 1;

    swap_values(tab, value1, value2);
}
/* stara verzija funkcije generiranja tabele
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
*/
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
    // parametra sta ostala zaradi obstoječih klicev funkcije
    (void)row;
    (void)col;
    
    int best_row = -1;
    int best_col = -1;
    int best_options = 10;
    int best_values[9];
    int best_values_count = 0;

    

    // poiscemo prazno mesto z najmanj moznostmi
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(tab[i][j] == 0){
                int candidates[9];
                int options = 0;

                // shranimo dovoljene vrednosti za trenutno prazno mesto
                for(int value = 1; value <= 9; value++){
                    if(check_value(tab, i, j, value)){
                        candidates[options] = value;
                        options++;
                    }
                }

                // ce mesto nima nobene moznosti, ta veja nima resitve
                if(options == 0){
                    return 0;
                }

                // shranimo mesto z najmanj moznostmi
                if(options < best_options){
                    best_options = options;
                    best_row = i;
                    best_col = j;
                    best_values_count = options;

                    // shranimo dovoljene vrednosti za najboljse prazno mesto
                    for(int k = 0; k < options; k++){
                        best_values[k] = candidates[k];
                    }
                }
            }
        }
    }

    // ce ni vec praznih mest, smo nasli resitev
    if(best_row == -1){
        (*count)++;

        // ko najdemo drugo resitev, prekinemo iskanje
        if(*count >= 2){
            return 1;
        }

        return 0;
    }

    // poskusimo vse dovoljene vrednosti na izbranem mestu
    for(int k = 0; k < best_values_count; k++){
        int value = best_values[k];
        tab[best_row][best_col] = value;

        if(count_solutions(tab, 0, 0, count)){
            tab[best_row][best_col] = 0;
            return 1;
        }

        // odstranimo poskusno vrednost pred naslednjim poskusom
        tab[best_row][best_col] = 0;
    }

    return 0;
}

// odstranjuje vrednosti iz tabele, dokler ostane natanko ena resitev
int remove_values(int tab[9][9], int target_removed){
    // preveri, ali je zeleno stevilo odstranjenih mest v dovoljenem razponu
    if(target_removed < 1 || target_removed > 64){
        return 0;
    }

    int full_tab[9][9];
    memcpy(full_tab, tab, sizeof(full_tab));

    int max_retries = 2;
    int removed = 0;
    int positions[81];

    for(int attempt = 0; attempt < max_retries; attempt++){
        // pred vsakim poskusom obnovimo polno tabelo
        memcpy(tab, full_tab, sizeof(full_tab));
        removed = 0;

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
            if(removed == target_removed){
                return 1;
            }
        }
    }

    // vsi poskusi so bili neuspesni
    memcpy(tab, full_tab, sizeof(full_tab));
    return 0;
}

// generira novo sudoku uganko in shrani njeno polno resitev
int generate_puzzle(int tab[9][9], int solution[9][9], int target_removed){
    int full_tab[9][9];
    int base_tab[9][9];
    int success = 0;
    int attempts = 0;
    int max_attempts = 150;

    // ustvarimo zacetno veljavno sudoku tabelo
    create_base_tab(base_tab);

    // generiranje ponavljamo dokler ne dosezemo zazelenega
    // stevila odstranjenih mest ali maksimalnega stevila poskusov
    while(success == 0 && attempts < max_attempts){

        // kopiramo zacetno tabelo in jo nakljucno premesamo
        memcpy(tab, base_tab, sizeof(base_tab));
        randomize_tab(tab);

        // shranimo polno resitev, preden zacnemo odstranjevati vrednosti
        memcpy(full_tab, tab, sizeof(full_tab));

        // poskusimo odstraniti zazeleno stevilo vrednosti
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
                printf("Zacetnih vrednosti ne smete spreminjati. :)\n");
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


