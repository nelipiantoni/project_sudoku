# Sudoku

Projekt je napisan v programskem jeziku C in omogoča generiranje ter reševanje Sudoku ugank v terminalu.

## Funkcionalnosti

Program omogoča:
- generiranje naključne veljavne Sudoku tabele,
- generiranje Sudoku uganke z enolično rešitvijo,
- izbiro med tremi težavnostmi,
- reševanje uganke preko terminala,
- preverjanje uporabniških vnosov,
- zaščito začetnih vrednosti pred spreminjanjem,
- preverjanje pravilnosti končne rešitve.

Pri generiranju polne Sudoku tabele je uporabljen rekurzivni backtracking algoritem. Pri ustvarjanju uganke program naključno odstranjuje vrednosti in po vsaki odstranitvi preveri število možnih rešitev. Odstranitev obdrži samo, če ima uganka še vedno natanko eno rešitev.

## Težavnosti

Težavnost je določena s številom odstranjenih vrednosti:

- Easy: 40–45 odstranjenih mest
- Medium: 46–52 odstranjenih mest
- Hard: 53–59 odstranjenih mest

## Struktura projekta

- main.c – zagon programa, izbira težavnosti in inicializacija igre
- sudoku.c – implementacija generiranja, preverjanja in igranja Sudokuja
- sudoku.h – deklaracije funkcij

## Prevajanje programa

Program lahko prevedemo z GCC:

```bash
gcc -Wall -Wextra main.c sudoku.c -o sudoku
```

oziroma:

```bash
gcc main.c sudoku.c -o sudoku
```

Program nato zaženemo z:

```bash
./sudoku
```

## Uporaba

Ob zagonu uporabnik najprej izbere težavnost. Nato se v terminalu izpiše generirana Sudoku uganka.

Potezo uporabnik vnese v obliki:

```text
vrstica stolpec vrednost
```

Na primer:

```text
3 5 7
```

pomeni, da želimo v 3. vrstico in 5. stolpec vstaviti vrednost 7.

Pri vnosu uporabnik določi vrstico in stolpec s številom od 1 do 9 ter nato vnese vrednost od 1 do 9. Začetnih vrednosti Sudoku uganke ni mogoče spreminjati.

Igra se konča, ko je tabela v celoti in pravilno rešena.
