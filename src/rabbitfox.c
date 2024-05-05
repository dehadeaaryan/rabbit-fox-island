#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rabbitFoxIsland.h"

// Island grid
IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y];

int main() {
    srand(time(NULL)); // Seed the random number generator

    int choice;
    printf("Choose a case to run:\n");
    printf("1. Case 1: Uniformly, there are two foxes and 100 rabbits per square initially; the vegetation level is 1.0 everywhere.\n");
    printf("2. Case 2: There are 20 foxes in one corner square and none elsewhere; there are 10 rabbits in every square except in the corner square diagonally opposte the foxes, and it contains 800 rabbits; the vegetation level is 0.3 everywhere. \n");
    printf("3. Case 3: There are no foxes on the island, but there are two rabbits in each square; the initial vegetation level is 0.5 everywhere.\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    initializeIsland(choice);

    visualizeIsland();
    simulateIsland(1); // Simulate the island for one month

    return 0;
}

// Function to initialize the island with initial population values and vegetation levels
void initializeIsland(int caseNumber) {
int success = 1;
 for (int i = 0; i < GRID_SIZE_X; i++) {
        for (int j = 0; j < GRID_SIZE_Y; j++) {
            switch (caseNumber) {
                case 1:
                    island[i][j].rabbits = 100;
                    island[i][j].foxes = 2;
                    island[i][j].vegetation = 1.0;
                    island[i][j].rabbitLifespan = calculateRabbitLifespan(1.0);
                    break;
                case 2:
                    if (i == GRID_SIZE_X - 1 && j == GRID_SIZE_Y - 1) {
                        island[i][j].rabbits = 800;
                    } else {
                        island[i][j].rabbits = 10;
                    }
                    if (i == GRID_SIZE_X - 1 && j == GRID_SIZE_Y - 1) {
                        island[i][j].foxes = 20;
                    } else {
                        island[i][j].foxes = 0;
                    }
                    island[i][j].vegetation = 0.3;
                    island[i][j].rabbitLifespan = calculateRabbitLifespan(0.3);
                    break;
                case 3:
                    island[i][j].rabbits = 2;
                    island[i][j].foxes = 0;
                    island[i][j].vegetation = 0.5;
                    island[i][j].rabbitLifespan = calculateRabbitLifespan(0.5);
                    break;
                default:
                    printf("Invalid case number.\n");
                    success = 0; // Indicate failure
                    break;
            }
        }
    }

    if (!success) {
        return; // Return outside the parallel region
    }
}

// Function to visualize the island grid
void visualizeIsland() {
    for (int i = 0; i < GRID_SIZE_X; i++) {
        for (int j = 0; j < GRID_SIZE_Y; j++) {
            printf("V%.2f-F%d-R%d ", island[i][j].vegetation, island[i][j].foxes, island[i][j].rabbits);
        }
        printf("\n");
    }
}


// Function to determine the lifespan of rabbits based on Table 3
int calculateRabbitLifespan(double vegetationLevel) {
    if (vegetationLevel >= LOW_VEGETATION_LEVEL && vegetationLevel < MID_LOW_VEGETATION_LEVEL) {
        return 3; // Lifespan is 3 months
    } else if (vegetationLevel >= MID_LOW_VEGETATION_LEVEL && vegetationLevel < MID_HIGH_VEGETATION_LEVEL) {
        return 6; // Lifespan is 6 months
    } else if (vegetationLevel >= MID_HIGH_VEGETATION_LEVEL && vegetationLevel < HIGH_VEGETATION_LEVEL) {
        return 12; // Lifespan is 12 months
    } else {
        return 18; // Lifespan is 18 months
    }
}

// Usage example in your simulation loop
void simulateRabbitLifespan() {
    // Loop through each square in the island
    for (int i = 0; i < GRID_SIZE_X; i++) {
        for (int j = 0; j < GRID_SIZE_Y; j++) {
            // Calculate the lifespan of rabbits based on vegetation level
            island[i][j].rabbitLifespan = calculateRabbitLifespan(island[i][j].vegetation);
        }
    }
}

// Simulation function
void simulateIsland(int months) {
    int daysFor9Weeks = 7 * 9;
    int daysFor6Months = 30 * 6;
    for (int month = 0; month < months; month++) {
        printf("\nMonth %d:\n", month + 1);
        for (int day = 0; day < MONTH_DAYS * months; day++) {
            if ((day % daysFor9Weeks) == 0) {
                simulateRabbitReproduction(island);
            }
            if ((day % daysFor6Months) == 0) {
                simulateFoxReproduction(island);
            }
            simulateRabbitDeaths();
            simulateFoxDeaths();
            simulateRabbitLifespan();
            updateVegetation(island);
            printf("Day %d:\n", day + 1);
            visualizeIsland();
        }
        simulateMigration(island);
    }
}
