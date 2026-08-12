#include <stdio.h>
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

    // vrednosti od 1 do 9 vstavljamo v tabelo
    for(int value = 1; value <= 9; value++){

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