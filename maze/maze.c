#include "maze.h"

void print_maze(int **maze, int n, int m){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (maze[i][j] == -1)
                printf("#");
            else 
                printf("%i", maze[i][j]);
        }
        printf("\n");
    }
}

int** init_maze(int n, int m){
    int nb = 0;
    int** new_maze = (int**) malloc(n*sizeof(int*));
    for (int i = 0; i < n; i++){
        int* cur_row = (int*) malloc(m*sizeof(int));
        for (int j = 0; j < m; j++){
            cur_row[j] = (i % 2 == 0) ? -1 : (j % 2 == 0) ? -1 : nb++;
        }
        new_maze[i] = cur_row;
    }
    return new_maze;
}

void free_maze(int** maze, int n){
    for (int i = 0; i < n; i++)
        free(maze[i]);
    free(maze);
}

int card_class(int n, int m){
    return n * m - (m * (n + 1) / 2 + (m + 1) * (n - 1) / 4);
}

void prop_class(int** maze, int i, int j, int old, int new){
    maze[i][j] = new;
    if (maze[i-1][j] == old)
        prop_class(maze, i-1, j, old, new);
    if (maze[i+1][j] == old)
        prop_class(maze, i+1, j, old, new);
    if (maze[i][j-1] == old)
        prop_class(maze, i, j-1, old, new);
    if (maze[i][j+1] == old)
        prop_class(maze, i, j+1, old, new);
}

void create_maze(int** maze, int n, int m){
    int cc = card_class(n, m) - 1;

    while (cc > 0){
        int x = rand() % (n - 2) + 1;
        int y = (x % 2 == 0) ? ((rand() % ((m - 1) / 2))) * 2 + 1 
                             : ((rand() % ((m - 2) / 2))) * 2 + 2;
        if (maze[x][y] != -1)  // We verify we are on a wall
            continue;
        
        int cell1 = (maze[x-1][y] == -1) ? maze[x][y-1] : maze[x-1][y];
        int cell2 = (maze[x-1][y] == -1) ? maze[x][y+1] : maze[x+1][y];

        if (cell1 != cell2){
            if (rand() % 2 == 0)
                prop_class(maze, x, y, cell1, cell2);
            else 
                prop_class(maze, x, y, cell2, cell1);
            cc--;
        }
    }

    #if COMPLEX != 0
        int i = 0;
        while (i < COMPLEX){
            int x = rand() % (n - 2) + 1;
            int y = (x % 2 == 0) ? ((rand() % ((m - 1) / 2))) * 2 + 1 
                                 : ((rand() % ((m - 2) / 2))) * 2 + 2;
            if (maze[x][y] != -1)  // We verify we are on a wall
                continue;

            int cell = (maze[x-1][y] == -1) ? maze[x][y-1] : maze[x-1][y];
            maze[x][y] = cell;
            i++;
        }
    #endif 

    // Start and end
    maze[1][0] = maze[1][1];
    maze[n-2][m-1] = maze[n-2][m-2];

}

int main(int argc, char* argv[]){

    srand(time(NULL));

    int n = 7;
    int m = 7;

    int** maze = init_maze(n, m);
    create_maze(maze, n, m);
    print_maze(maze, n, m);
    free_maze(maze, n);

    // initscr();
    // printw("Hello World");
    // refresh();
    // getch();
    // endwin();


    return EXIT_SUCCESS;
}
