#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rabbitFoxIsland.h"

IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y];

int ages[INITIAL_RABBITS] = {0};

void initializeIsland() {
    for (int i = 0; i < GRID_SIZE_X; i++) {
        for (int j = 0; j < GRID_SIZE_Y; j++) {
            island[i][j].rabbits = INITIAL_RABBITS;
            island[i][j].foxes = INITIAL_FOXES;
            island[i][j].vegetation = INITIAL_VEGETATION;
        }
    }
}

void visualizeIsland() {
    for (int i = 0; i < GRID_SIZE_X; i++) {
        for (int j = 0; j < GRID_SIZE_Y; j++) {
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

void rabbitReproductionEvent() {
    for (int i = 0; i < GRID_SIZE_X; i++) {
        for (int j = 0; j < GRID_SIZE_Y; j++) {
            int babyRabbits = calculateBabyRabbits(island[i][j].vegetation, island[i][j].rabbits);
            island[i][j].rabbits += babyRabbits;
        }
    }
}

void foxReproductionEvent() {
    for (int i = 0; i < GRID_SIZE_X; i++) {
        for (int j = 0; j < GRID_SIZE_Y; j++) {
            int foxKits = calculateFoxKits(island[i][j].rabbits, island[i][j].foxes);
            island[i][j].foxes += foxKits;
        }
    }
}

void simulateIsland(int years) {
    srand(time(NULL)); // Seed the random number generator
    for (int year = 0; year < years; year++) {
        printf("\nYear %d:\n", year + 1);
        for (int day = 0; day < 365; day++) {
            if ((day % (7 * 9)) == 0) {
                // Call rabbit reproduction event every nine weeks
                rabbitReproductionEvent();
            }
            if ((day % (30 * 6)) == 0) {
                // Call fox reproduction event every six months
                foxReproductionEvent();
            }
            // Simulate vegetation growth
            updateVegetation(island);
            // Simulate rabbit and fox migration
            simulateMigration(island);
            // Simulate rabbit deaths due to various factors
            simulateRabbitDeaths();
            // Simulate fox deaths due to various factors
            simulateFoxDeaths();

            printf("Day %d:\n", day + 1);
            visualizeIsland();
        }
    }
}

int main() {
    initializeIsland();
    visualizeIsland();
    simulateIsland(YEARS_TO_SIMULATE);
    return 0;
}
