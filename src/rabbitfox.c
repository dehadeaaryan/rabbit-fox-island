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

// Define constants for ranges of vegetation levels
#define LOW_VEGETATION_LEVEL 0.1
#define MID_LOW_VEGETATION_LEVEL 0.15
#define MID_HIGH_VEGETATION_LEVEL 0.25
#define HIGH_VEGETATION_LEVEL 0.35

typedef struct 
{
    int rabbits;
    int foxes;
    double vegetation;
    int rabbitLifespan; // Added to store the lifespan of rabbits
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
            
            // Calculate the lifespan of rabbits based on the initial vegetation level
            if (island[i][j].vegetation >= LOW_VEGETATION_LEVEL && island[i][j].vegetation < MID_LOW_VEGETATION_LEVEL) {
                island[i][j].rabbitLifespan = 3; // Lifespan is 3 months
            } else if (island[i][j].vegetation >= MID_LOW_VEGETATION_LEVEL && island[i][j].vegetation < MID_HIGH_VEGETATION_LEVEL) {
                island[i][j].rabbitLifespan = 6; // Lifespan is 6 months
            } else if (island[i][j].vegetation >= MID_HIGH_VEGETATION_LEVEL && island[i][j].vegetation < HIGH_VEGETATION_LEVEL) {
                island[i][j].rabbitLifespan = 12; // Lifespan is 12 months
            } else {
                island[i][j].rabbitLifespan = 18; // Lifespan is 18 months
            }
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

// Rabbit Deaths
void simulateRabbitDeaths()
{
    for (int i = 0; i < GRID_SIZE_X; i++)
    {
        for (int j = 0; j < GRID_SIZE_Y; j++)
        {
            int totalDeaths = 0;
            int randomNumber = rand() % 100 + 1;
            if (randomNumber <= 10)
            { 
                totalDeaths++;
            }
            if (island[i][j].vegetation < LOW_VEGETATION_LEVEL)
            {
                totalDeaths += 3;
            }
            island[i][j].rabbits -= totalDeaths;
            if (island[i][j].rabbits < 0)
            {
                island[i][j].rabbits = 0;
            }
        }
    }
}

// Fox Deaths
void simulateFoxDeaths()
{
    for (int i = 0; i < GRID_SIZE_X; i++)
    {
        for (int j = 0; j < GRID_SIZE_Y; j++)
        {
            double deathChance = calculateFoxDeathChance(island[i][j].foxes);
            double randomNumber = (double)rand() / RAND_MAX;
            if (randomNumber < deathChance)
            {
                island[i][j].foxes--;
                if (island[i][j].foxes < 0)
                {
                    island[i][j].foxes = 0;
                }
            }
        }
    }
}

void reproductionEvent() {
    // Loop through each square in the island
    for (int i = 0; i < GRID_SIZE_X; i++) {
        for (int j = 0; j < GRID_SIZE_Y; j++) {
            // Calculate the number of baby rabbits born based on vegetation level and initial number of rabbits
            int babyRabbits = calculateBabyRabbits(island[i][j].vegetation, island[i][j].rabbits);
            
            // Add the baby rabbits to the population of rabbits in the square
            island[i][j].rabbits += babyRabbits;
        }
    }
}


void foxReproductionEvent() {
    // Loop through each square in the island
    for (int i = 0; i < GRID_SIZE_X; i++) {
        for (int j = 0; j < GRID_SIZE_Y; j++) {
            // Calculate the number of fox kits born based on initial number of rabbits and foxes
            int foxKits = calculateFoxKits(island[i][j].rabbits, island[i][j].foxes);
            
            // Add the fox kits to the population of foxes in the square
            island[i][j].foxes += foxKits;
        }
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

// Function to determine the chance of a fox dying
double calculateFoxDeathChance(int initialFoxes) {
    if (initialFoxes < LOW_FOXES) {
        return 0.1; // 10% chance of dying
    } else if (initialFoxes < MID_LOW_FOXES) {
        return 0.2; // 20% chance of dying
    } else if (initialFoxes < MID_HIGH_FOXES) {
        return 0.3; // 30% chance of dying
    } else {
        return 0.4; // 40% chance of dying
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

// Function to simulate the island for a given number of years
void simulateIsland(int years)
{
    // Loop over each day for the specified number of years
    for (int year = 0; year < years; year++)
    {
        // Print the year number
        printf("\nYear %d:\n", year + 1);

        // Simulate each day in the current year
        for (int day = 0; day < 365; day++)
        {
            // Check if it's a birthing day for rabbits (every nine weeks)
            if ((day % (7 * 9)) == 0)
            {
                // Call function to simulate birthing events for rabbits
                reproductionEvent();
            }

            // Check if it's a birthing day for foxes (every six months)
            if ((day % (30 * 6)) == 0)
            {
                // Call function to simulate birthing events for foxes
                foxReproductionEvent();
            }

            // Print visualized island after each day's simulation
            printf("Day %d:\n", day + 1);
            visualizeIsland();
        }
    }
}

int main()
{
    srand(time(NULL)); // Seed the random number generator

    initializeIsland();
    visualizeIsland();

    // Simulate the island for the specified number of years
    simulateIsland(YEARS_TO_SIMULATE);

    return 0;
}
