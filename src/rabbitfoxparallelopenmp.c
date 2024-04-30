#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rabbitFoxIsland.h"

typedef struct {
    int rabbits;
    int foxes;
    double vegetation;
} IslandSquare;

IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y];

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

void simulateRabbitDeaths() {
    for (int i = 0; i < GRID_SIZE_X; i++) {
        for (int j = 0; j < GRID_SIZE_Y; j++) {
            int totalDeaths = 0;
            int randomNumber = rand() % 100 + 1;
            if (randomNumber <= 10) { 
                totalDeaths++;
            }
            if (island[i][j].vegetation < LOW_VEGETATION_LEVEL) {
                totalDeaths += 3;
            }
            island[i][j].rabbits -= totalDeaths;
            if (island[i][j].rabbits < 0) {
                island[i][j].rabbits = 0;
            }
        }
    }
}

void simulateFoxDeaths() {
    for (int i = 0; i < GRID_SIZE_X; i++) {
        for (int j = 0; j < GRID_SIZE_Y; j++) {
            double deathChance = calculateFoxDeathChance(island[i][j].foxes);
            double randomNumber = (double)rand() / RAND_MAX;
            if (randomNumber < deathChance) {
                island[i][j].foxes--;
                if (island[i][j].foxes < 0) {
                    island[i][j].foxes = 0;
                }
            }
        }
    }
}

double calculateFoxDeathChance(int initialFoxes) {
    if (initialFoxes < 11) {
        return 0.1;
    } else if (initialFoxes < 51) {
        return 0.2;
    } else {
        return 0.4;
    }
}

void reproductionEvent() {
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
    srand(time(NULL));
    for (int year = 0; year < years; year++) {
        printf("\nYear %d:\n", year + 1);
        for (int day = 0; day < 365; day++) {
            if ((day % (7 * 9)) == 0) {
                reproductionEvent();
            }
            if ((day % (30 * 6)) == 0) {
                foxReproductionEvent();
            }
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
