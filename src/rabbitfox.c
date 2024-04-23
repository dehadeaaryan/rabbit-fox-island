// gcc -o rabbitfox rabbitfox.c

#include <stdio.h>

#define GRID_SIZE_X 8 
#define GRID_SIZE_Y 8 

// Define initial conditions
#define INITIAL_RABBITS 10
#define INITIAL_FOXES 5
#define INITIAL_VEGETATION 0.5

typedef struct 
{
    int rabbits;
    int foxes;
    double vegetation;
} IslandSquare;

//Initializing the island grid (64 boxes)
IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y];

// Function to initialize the island with initial population values and vegetation levels
void initializeIsland() {
    int i, j;
    for (i = 0; i < GRID_SIZE_X; i++) {
        for (j = 0; j < GRID_SIZE_Y; j++) {
            // Initialize rabbits, foxes, and vegetation for each square
            island[i][j].rabbits = INITIAL_RABBITS;
            island[i][j].foxes = INITIAL_FOXES;
            island[i][j].vegetation = INITIAL_VEGETATION;
        }
    }
}

// Function to visualize the island grid
void visualizeIsland() {
    int i, j;
    for (i = 0; i < GRID_SIZE_X; i++) {
        for (j = 0; j < GRID_SIZE_Y; j++) {
            if (island[i][j].foxes > 0) {
                printf("F");
            } else if (island[i][j].vegetation > 0.5) {
                printf("#");
            } else if (island[i][j].rabbits > 0) {
                printf("R");
            } else {
                printf(".");
            }
            printf(" ");
        }
        printf("\n");
    }
}



int main() {
    initializeIsland();
    visualizeIsland();
    return 0;
}