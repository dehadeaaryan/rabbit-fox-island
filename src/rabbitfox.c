#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GRID_SIZE_X 8 
#define GRID_SIZE_Y 8 
#define MONTH_DAYS 30

// Define initial conditions
#define INITIAL_RABBITS 10
#define INITIAL_FOXES 5
#define INITIAL_VEGETATION 0.5

// Define constants for ranges of vegetation levels and initial number of rabbits
#define LOW_VEGETATION_LEVEL 0.1
#define MID_LOW_VEGETATION_LEVEL 0.15
#define MID_HIGH_VEGETATION_LEVEL 0.25
#define HIGH_VEGETATION_LEVEL 0.35

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

// Define functions
void initializeIsland();
void visualizeIsland();
int calculateBabyRabbits(double vegetation, int initialRabbits);
int calculateFoxKits(int initialRabbits, int initialFoxes);
void simulateRabbitDeaths();
double calculateFoxDeathChance(int initialFoxes);
void simulateFoxDeaths();
void reproductionEvent();
void foxReproductionEvent();
int calculateRabbitLifespan(double vegetationLevel);
void simulateRabbitLifespan();
void simulateIsland(int months);
void updateVegetation();

// Island square structure
typedef struct {
    int rabbits;
    int foxes;
    double vegetation;
    int rabbitLifespan;
} IslandSquare;

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
void initializeIsland(caseNumber) {
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
            printf("F%dR%d ", island[i][j].foxes, island[i][j].rabbits);
        }
        printf("\n");
    }
}


// Rabbit birth
int calculateBabyRabbits(double vegetation, int initialRabbits) {
    if (vegetation < LOW_VEGETATION_LEVEL) {
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
    } else if (vegetation < MID_LOW_VEGETATION_LEVEL) {
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
    } else if (vegetation < HIGH_VEGETATION_LEVEL) {
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


// Fox Deaths
void simulateFoxDeaths()
{
    for (int i = 0; i < GRID_SIZE_X; i++)
    {
        for (int j = 0; j < GRID_SIZE_Y; j++)
        {
            // Calculate the chance of a fox dying due to natural causes
            double naturalDeathChance = 0.1; // 10% chance of natural death

            // Calculate the chance of a fox eating a rabbit based on vegetation level and rabbit availability
            double eatRabbitChance;
            if (island[i][j].vegetation < 0.6 && island[i][j].rabbits >= 4)
            {
                eatRabbitChance = 4.0 / 7.0;
            }
            else if (island[i][j].rabbits >= 2)
            {
                eatRabbitChance = 2.0 / 7.0;
            }
            else
            {
                eatRabbitChance = 0.0;
            }

            // Generate a random number to determine if a fox dies due to natural causes
            double naturalDeathRandom = (double)rand() / RAND_MAX;
            if (naturalDeathRandom < naturalDeathChance)
            {
                // Fox dies due to natural causes
                island[i][j].foxes--;
                if (island[i][j].foxes < 0)
                {
                    island[i][j].foxes = 0;
                }
            }

            // Generate a random number to determine if a fox dies due to lack of food
            if (island[i][j].foxes > 0 && eatRabbitChance > 0)
            {
                double eatRabbitRandom = (double)rand() / RAND_MAX;
                if (eatRabbitRandom < eatRabbitChance)
                {
                    // Fox eats a rabbit
                    island[i][j].rabbits--;
                    if (island[i][j].rabbits < 0)
                    {
                        island[i][j].rabbits = 0;
                    }
                }
                else
                {
                    // Fox doesn't eat a rabbit, check if it dies due to lack of food
                    double starvationDeathRandom = (double)rand() / RAND_MAX;
                    if (starvationDeathRandom < 0.1) // 10% chance of starvation death
                    {
                        // Fox dies due to starvation
                        island[i][j].foxes--;
                        if (island[i][j].foxes < 0)
                        {
                            island[i][j].foxes = 0;
                        }
                    }
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
    for (int month = 0; month < months; month++) {
        printf("\nMonth %d:\n", month + 1);
        for (int day = 0; day < MONTH_DAYS * months; day++) {
            if ((day % (7 * 9)) == 0) {
                reproductionEvent();
            }
            if ((day % (30 * 6)) == 0) {
                foxReproductionEvent();
            }
            simulateRabbitDeaths();
            simulateFoxDeaths();
            simulateRabbitLifespan();
            updateVegetation();
            printf("Day %d:\n", day + 1);
            visualizeIsland();
        }
    }
}

// Vegetation Update function
void updateVegetation() {
    for (int i = 0; i < GRID_SIZE_X; i++) {
        for (int j = 0; j < GRID_SIZE_Y; j++) { 
            // Formula
            double vegetationChange = (island[i][j].vegetation * 1.1) - (0.001 * island[i][j].rabbits);
            if (vegetationChange < LOW_VEGETATION_LEVEL) {
                island[i][j].vegetation = LOW_VEGETATION_LEVEL;
            }
            else if (vegetationChange > HIGH_VEGETATION_LEVEL) {
                island[i][j].vegetation = HIGH_VEGETATION_LEVEL;
            }
            else {
                island[i][j].vegetation = vegetationChange;
            }
        }
    }
}
