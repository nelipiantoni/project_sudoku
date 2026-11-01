int check_value(int tab[9][9], int row, int col, int value);

void swap_rows(int tab[9][9], int row1, int row2);

void swap_columns(int tab[9][9], int col1, int col2);

void swap_row_groups(int tab[9][9], int group1, int group2);

void swap_column_groups(int tab[9][9], int group1, int group2);

void swap_values(int tab[9][9], int value1, int value2);

void create_base_tab(int tab[9][9]);

void randomize_tab(int tab[9][9]);

int generate_tab(int tab[9][9], int row, int col);

void print_tab(int tab[9][9]);

int remove_values(int tab[9][9], int target_removed);

int count_solutions(int tab[9][9], int row, int col, int *count);

int generate_puzzle(int tab[9][9], int solution[9][9], int target_removed);

int play_sudoku(int tab[9][9], int original[9][9], int solution[9][9]);

int is_complete(int tab[9][9]);

int check_solution(int tab[9][9], int solution[9][9]);