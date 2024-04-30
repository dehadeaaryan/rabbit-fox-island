#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GRID_SIZE_X 8 
#define GRID_SIZE_Y 8 
#define YEARS_TO_SIMULATE 100

// Define initial conditions
#define INITIAL_RABBITS 10
#define INITIAL_FOXES 5
#define INITIAL_VEGETATION 0.5

// Define constants for ranges of vegetation levels and initial number of rabbits
#define LOW_VEGETATION 0.2
#define MID_VEGETATION 0.5
#define HIGH_VEGETATION 0.8

#define LOW_RABBITS_T1 2
#define MID_LOW_RABBITS_T1 201
#define MID_HIGH_RABBITS_T1 701
#define HIGH_RABBITS_T1 5001

#define LOW_RABBITS_FOX 3
#define MID_RABBITS_FOX 10
#define HIGH_RABBITS_FOX 40

#define LOW_FOXES 2
#define MID_LOW_FOXES 11
#define MID_HIGH_FOXES 51
#define HIGH_FOXES 100

#define LOW_VEGETATION_LEVEL 0.1
#define MID_LOW_VEGETATION_LEVEL 0.15
#define MID_HIGH_VEGETATION_LEVEL 0.25
#define HIGH_VEGETATION_LEVEL 0.35

typedef struct {
    int rabbits;
    int foxes;
    double vegetation;
    int rabbitLifespan;
} IslandSquare;

IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y];

void initializeIsland() {
    for (int i = 0; i < GRID_SIZE_X; i++) {
        for (int j = 0; j < GRID_SIZE_Y; j++) {
            island[i][j].rabbits = INITIAL_RABBITS;
            island[i][j].foxes = INITIAL_FOXES;
            island[i][j].vegetation = INITIAL_VEGETATION;
            island[i][j].rabbitLifespan = 0; // Initialize lifespan
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

// Rabbit birth
int calculateBabyRabbits(double vegetation, int initialRabbits) {
    if (vegetation < LOW_VEGETATION) {
        if (initialRabbits < LOW_RABBITS_T1) {
            return 0;
        } else if (initialRabbits < MID_LOW_RABBITS_T1) {
            return 3;
        } else if (initialRabbits < MID_HIGH_RABBITS_T1) {
            return 3;
        } else if (initialRabbits < HIGH_RABBITS_T1) {
            return 2;
        } else {
            return 2;
        }
    } else if (vegetation < MID_VEGETATION) {
        if (initialRabbits < LOW_RABBITS_T1) {
            return 0;
        } else if (initialRabbits < MID_LOW_RABBITS_T1) {
            return 4;
        } else if (initialRabbits < MID_HIGH_RABBITS_T1) {
            return 4;
        } else if (initialRabbits < HIGH_RABBITS_T1) {
            return 3;
        } else {
            return 3;
        }
    } else if (vegetation < HIGH_VEGETATION) {
        if (initialRabbits < LOW_RABBITS_T1) {
            return 0;
        } else if (initialRabbits < MID_LOW_RABBITS_T1) {
            return 6;
        } else if (initialRabbits < MID_HIGH_RABBITS_T1) {
            return 5;
        } else if (initialRabbits < HIGH_RABBITS_T1) {
            return 4;
        } else {
            return 4;
        }
    } else {
        if (initialRabbits < LOW_RABBITS_T1) {
            return 0;
        } else if (initialRabbits < MID_LOW_RABBITS_T1) {
            return 9;
        } else if (initialRabbits < MID_HIGH_RABBITS_T1) {
            return 8;
        } else if (initialRabbits < HIGH_RABBITS_T1) {
            return 7;
        } else {
            return 5;
        }
    }
}

// Fox Birth
int calculateFoxKits(int initialRabbits, int initialFoxes) {
    if (initialRabbits < LOW_RABBITS_FOX) {
        if (initialFoxes < LOW_FOXES) {
            return 0;
        } else if (initialFoxes < MID_LOW_FOXES) {
            return 2;
        } else if (initialFoxes < MID_HIGH_FOXES) {
            return 2;
        } else if (initialFoxes < HIGH_FOXES) {
            return 1;
        } else {
            return 0;
        }
    } else if (initialRabbits < MID_RABBITS_FOX) {
        if (initialFoxes < LOW_FOXES) {
            return 0;
        } else if (initialFoxes < MID_LOW_FOXES) {
            return 3;
        } else if (initialFoxes < MID_HIGH_FOXES) {
            return 3;
        } else if (initialFoxes < HIGH_FOXES) {
            return 2;
        } else {
            return 1;
        }
    } else if (initialRabbits < HIGH_RABBITS_FOX) {
        if (initialFoxes < LOW_FOXES) {
            return 0;
        } else if (initialFoxes < MID_LOW_FOXES) {
            return 4;
        } else if (initialFoxes < MID_HIGH_FOXES) {
            return 3;
        } else if (initialFoxes < HIGH_FOXES) {
            return 3;
        } else {
            return 2;
        }
    } else {
        if (initialFoxes < LOW_FOXES) {
            return 0;
        } else if (initialFoxes < MID_LOW_FOXES) {
            return 5;
        } else if (initialFoxes < MID_HIGH_FOXES) {
            return 4;
        } else if (initialFoxes < HIGH_FOXES) {
            return 3;
        } else {
            return 3;
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
