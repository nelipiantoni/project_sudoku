#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sudoku.h"


//funkcija za preverjanje, ali smemo stevilo sploh vstaviti na to mesto
int check_value(int tab[9][9], int row, int col, int value){
    int start_row;
    int start_col;

    //preverja vrstico
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
    // isce zacetno vrstico in stolpec pregledovanja za kvadrat
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

    // pregleduje kvadrat
    for(int i = start_row; i < start_row + 3; i++){
        for(int j = start_col; j < start_col + 3; j++){
            if(tab[i][j] == value){
                return 0;
            }
        }
    }
    // ce funkcija prej ni vrnila 0 (false), vrne true kar pomeni, da lahko vstavimo stevilo 
    return 1;
}

// funkcija za generiranje tabele z rekurzijo
int generate_tab(int tab[9][9], int row, int col){

    //prisli smo cez zadnjo vrstico, tabela je uspesno zgenerirana
    if(row > 8){
        return 1;
    }

    int values[9] = {1,2,3,4,5,6,7,8,9};

    // algoritem za izbiranje nakljucnih stevil od 1 do 9
    for(int i = 8; i > 0; i--){
        int x = rand() % (i + 1);

        int y = values[i];
        values[i] = values[x];
        values[x] = y;
    }

    // vstavljanje nakljucnih vrednosti iz tabele
    for(int i = 0; i < 9; i++){
        int value = values[i];

        // preverjamo ce vrednost lahko vstavimo v tabelo, vstopimo v funkcijo, ce check_value vrne 1
        if(check_value(tab, row, col, value)){

            // vstavimo vrednost v tabelo
            tab[row][col] = value;

            // preverimo ali bomo v zadnjem stolpcu, ce bomo, rekurzivni premik v naslednjo vrstico
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
    // na temu mestu ni mozne veljavlne vrednosti, gremo en rekurzivni korak nazaj
    return 0;
    
}

//printa generirano polno tabelo v terminal
void print_tab(int tab[9][9]){

    // gremo cez vsa mesta v tabeli
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            // print vsake vrednosti v vrstici
            printf("%d ", tab[i][j]);
        }
        // preskok na naslednjo vrstico
        printf("\n");
    }
}

// stetje koliko resitev ima tabela po odstranjenem mestu
int count_solutions(int tab[9][9], int row, int col, int *count){

    // ko je tabela izpolnjena
    if(row > 8){
        // vrednost na naslovu kazalca se poveca za 1
        (*count)++;
        // return 1 poslje signal skozi vse prejsnje rekurzivne klice dokler ne pride nazaj do remove_value
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
            //preveri ali smemo vstaviti vrednost na to mesto
            if(check_value(tab, row, col, value)){
                //spremenimo vrednost
                tab[row][col] = value;
                // ce nalsednji klic count_solution vraca 1 returna tudi to izvajanje 1
                if(col < 8){
                    if(count_solutions(tab, row, col + 1, count)){
                        tab[row][col] = 0;
                        return 1;
                    }
                } else{
                    if(count_solutions(tab, row + 1, 0, count)){
                        tab[row][col] = 0;
                        return 1;
                    }
                }
            }
            tab[row][col] = 0;
        }
    // ce mesto v tabeli ni prazno, gledamo za naslednji klic count_solution ali je prazen, ce je funckija naprej tece
    } else{
        if(col < 8){
            if(count_solutions(tab, row, col + 1, count)){
                return 1;
            }
        } else{
            if(count_solutions(tab, row + 1, 0, count)){
                return 1;
            }
        }
}
    // ce nic od navedenega ne velja se vrnemo na prejsnji rekurzivni klic in iscemo naprej
    return 0;

}

//odstranjuje vrednosti iz tabele, dokler ima tabela se vedno eno resitev
int remove_values(int tab[9][9], int target_removed){
    // preverja, da ne gremo cez meje odstranjevanja vrednosti
    if(target_removed < 1 || target_removed > 64){
        return 0;
    }

    int removed = 0;
    int positions[81];

    for(int i = 0; i < 81; i++){
        positions[i] = i;
    }
    // algoritem za randomizacijo mest v tabeli positions
    for(int i = 80; i > 0; i--){
        int x = rand() % (i + 1);

        int y = positions[i];
        positions[i] = positions[x];
        positions[x] = y;
    }

    for(int i = 0; i < 81; i++){
        int row = positions[i] / 9;
        int col = positions[i] % 9;
        //shrani staro vrednost, da je lahko vrnemo kasneje nazaj, ce tabela nima vec ene resitve
        int old_value = tab[row][col];
        tab[row][col] = 0;
        int count = 0;
        
        count_solutions(tab, 0, 0, &count);

        //ce je stevilo resitev enako 1 potem se poveca stevec za odstranjena stevila, drugace vrednost v tabeli vrnemo nazaj na prejsnjo
        if(count == 1){
            removed++;
        } else{
            tab[row][col] = old_value;
        }

        //ce smo dosegli zazeljeno stevilo odstranjenih stevil
        if(target_removed == removed){
            return 1;
        }
        
    }
    //ce smo pogledali celo tabelo in nismo dosegli clija
    return 0;
}

