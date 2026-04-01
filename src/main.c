#include "raylib.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define GRID_CELL_SIZE              10
#define MAX_GRID_CELLS_X            130
#define MAX_GRID_CELLS_Y            100

int regle1(int grid[MAX_GRID_CELLS_X][MAX_GRID_CELLS_Y], int x, int y) {
    int ul = (x==0 && y==0)?0:grid[x-1][y-1];
    int ml = y==0?0:grid[x][y-1];
    int dl = (x==MAX_GRID_CELLS_X-1 && y==0)?0:grid[x+1][y-1];
    int uc = x==0?0:grid[x-1][y];
    int self = grid[x][y];
    int dc = x==MAX_GRID_CELLS_X-1?0:grid[x+1][y];
    int dr = (x==MAX_GRID_CELLS_X-1 && y==MAX_GRID_CELLS_Y-1)?0:grid[x+1][y+1];
    int mr = y==MAX_GRID_CELLS_Y-1?0:grid[x][y+1];
    int ur = (x==0 && y==MAX_GRID_CELLS_Y-1)?0:grid[x-1][y+1];
    printf("%d\n", (ul+ml+dl+uc+dc+dr+mr+ur));

    return self==0 && (ul+ml+dl+uc+dc+dr+mr+ur)==3;
}

int regle2(int grid[MAX_GRID_CELLS_X][MAX_GRID_CELLS_Y], int x, int y) {
    int ul = (x==0 && y==0)?0:grid[x-1][y-1];
    int ml = y==0?0:grid[x][y-1];
    int dl = (x==MAX_GRID_CELLS_X-1 && y==0)?0:grid[x+1][y-1];
    int uc = x==0?0:grid[x-1][y];
    int self = grid[x][y];
    int dc = x==MAX_GRID_CELLS_X-1?0:grid[x+1][y];
    int dr = (x==MAX_GRID_CELLS_X-1 && y==MAX_GRID_CELLS_Y-1)?0:grid[x+1][y+1];
    int mr = y==MAX_GRID_CELLS_Y-1?0:grid[x][y+1];
    int ur = (x==0 && y==MAX_GRID_CELLS_Y-1)?0:grid[x-1][y+1];
    printf("%d\n", (ul+ml+dl+uc+dc+dr+mr+ur));
    return self==1 && ((ul+ml+dl+uc+dc+dr+mr+ur)==2 || (ul+ml+dl+uc+dc+dr+mr+ur)==3);
}

int main(void) {

    const int screenWidth = (MAX_GRID_CELLS_X*GRID_CELL_SIZE)+GRID_CELL_SIZE*2;
    const int screenHeight = (MAX_GRID_CELLS_Y*GRID_CELL_SIZE)+GRID_CELL_SIZE*2;

    InitWindow(screenWidth, screenHeight, "game of life");

    Vector2 gridPosition = { GRID_CELL_SIZE, GRID_CELL_SIZE };
    srand(time(NULL));
    int grid[MAX_GRID_CELLS_X][MAX_GRID_CELLS_Y] = {0};
    for(int i = 0; i < MAX_GRID_CELLS_X; i++) {
        for(int j = 0; j < MAX_GRID_CELLS_Y; j++){
            grid[i][j] = rand()%2;      
        }
    }

    for (int i = 0; i < MAX_GRID_CELLS_X; i++) {
        for (int j = 0; j < MAX_GRID_CELLS_Y; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }


    for(int i = 0; i < MAX_GRID_CELLS_X; i++) {
        for(int j = 0; j < MAX_GRID_CELLS_Y; j++){
            if(grid[i][j]==1) {
                DrawRectangle((int)gridPosition.x + i*GRID_CELL_SIZE, (int)gridPosition.y + j*GRID_CELL_SIZE,
                    GRID_CELL_SIZE, GRID_CELL_SIZE, RAYWHITE);
            }
            if(grid[i][j]==0){
                DrawRectangle((int)gridPosition.x + i*GRID_CELL_SIZE, (int)gridPosition.y + j*GRID_CELL_SIZE,
                    GRID_CELL_SIZE, GRID_CELL_SIZE, BLACK);
            }    
        }
    }
    int frame_count = 0;
    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(BLACK);

            int new_grid[MAX_GRID_CELLS_X][MAX_GRID_CELLS_Y] = {0};

            for(int i = 0; i < MAX_GRID_CELLS_X; i++) {
                for(int j = 0; j < MAX_GRID_CELLS_Y; j++){
                    if(regle1(grid, i,j)) {
                        new_grid[i][j] = 1;
                    }
                    else if(regle2(grid, i, j)){
                        new_grid[i][j] = 1;
                    }
                    else {
                        new_grid[i][j] = 0;
                    }
                }
            }

            for(int i = 0; i < MAX_GRID_CELLS_X; i++) {
                for(int j = 0; j < MAX_GRID_CELLS_Y; j++){
                    grid[i][j] = new_grid[i][j];
                }
            }

            for(int i = 0; i < MAX_GRID_CELLS_X; i++) {
                for(int j = 0; j < MAX_GRID_CELLS_Y; j++){
                    Color color = grid[i][j]?RAYWHITE:BLACK;

                    DrawRectangle((int)gridPosition.x + i*GRID_CELL_SIZE, (int)gridPosition.y + j*GRID_CELL_SIZE,
                                GRID_CELL_SIZE, GRID_CELL_SIZE, color);

                }
            }

            for (int y = 0; y <= MAX_GRID_CELLS_Y; y++)
                DrawLine((int)gridPosition.x, (int)gridPosition.y + y*GRID_CELL_SIZE,
                    (int)gridPosition.x + MAX_GRID_CELLS_X*GRID_CELL_SIZE, (int)gridPosition.y + y*GRID_CELL_SIZE, GRAY);
            for (int x = 0; x <= MAX_GRID_CELLS_X; x++)
                DrawLine((int)gridPosition.x + x*GRID_CELL_SIZE, (int)gridPosition.y,
                    (int)gridPosition.x + x*GRID_CELL_SIZE, (int)gridPosition.y + MAX_GRID_CELLS_Y*GRID_CELL_SIZE, GRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}