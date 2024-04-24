#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GRID_SIZE_X 8 
#define GRID_SIZE_Y 8 

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

#define LOW_RABBITS_T2 2
#define MID_LOW_RABBITS_T2 11
#define MID_HIGH_RABBITS_T2 51
#define HIGH_RABBITS_T2 101

#define LOW_FOXES 3
#define MID_LOW_FOXES 10
#define MID_HIGH_FOXES 40
#define HIGH_FOXES 101

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

// Function to determine the number of baby rabbits born based on Table 1
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
        // logic for mid-range vegetation
    } else if (vegetation < HIGH_VEGETATION) {
        // logic for high-range vegetation
    } else {
        // handle case where vegetation level is very high
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


// Function to determine the number of fox kits born based on Table 2
int calculateFoxKits(int initialRabbits, int initialFoxes) {
    if (initialRabbits < LOW_RABBITS_T2) {
        return 0;
    } else if (initialRabbits < MID_LOW_RABBITS_T2) {
        if (initialFoxes >= LOW_FOXES && initialFoxes < MID_LOW_FOXES) {
            return 2;
        }
    } else if (initialRabbits < MID_HIGH_RABBITS_T2) {
        // Implement logic for mid-range rabbits
    } else if (initialRabbits < HIGH_RABBITS_T2) {
        // Implement logic for high-range rabbits
    }

    return 0; // Default case if no fox kits are born
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

int main() {
    initializeIsland();
    visualizeIsland();
    
    // Simulate reproduction events for rabbits and foxes
    reproductionEvent();
    foxReproductionEvent();
    
    // Print visualized island after simulation
    printf("\nAfter reproduction events:\n");
    visualizeIsland();
    
    // Simulate rabbit lifespan
    simulateRabbitLifespan();
    
    return 0;
}