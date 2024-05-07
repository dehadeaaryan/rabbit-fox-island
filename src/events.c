#include "events.h"

// Function to calculate the number of baby rabbits based on the vegetation level and initial rabbit population
int caluclateRabbitLitterSize(double vegetation, int initialRabbits)
{
    if (vegetation < LOW_VEGETATION)
    {
        if (initialRabbits < LOW_RABBITS_T1)
        {
            return 0;
        }
        else if (initialRabbits < MID_LOW_RABBITS_T1)
        {
            return 3;
        }
        else if (initialRabbits < MID_HIGH_RABBITS_T1)
        {
            return 3;
        }
        else if (initialRabbits < HIGH_RABBITS_T1)
        {
            return 2;
        }
        else
        {
            return 2;
        }
    }
    else if (vegetation < MID_VEGETATION)
    {
        if (initialRabbits < LOW_RABBITS_T1)
        {
            return 0;
        }
        else if (initialRabbits < MID_LOW_RABBITS_T1)
        {
            return 4;
        }
        else if (initialRabbits < MID_HIGH_RABBITS_T1)
        {
            return 4;
        }
        else if (initialRabbits < HIGH_RABBITS_T1)
        {
            return 3;
        }
        else
        {
            return 3;
        }
    }
    else if (vegetation < HIGH_VEGETATION)
    {
        if (initialRabbits < LOW_RABBITS_T1)
        {
            return 0;
        }
        else if (initialRabbits < MID_LOW_RABBITS_T1)
        {
            return 6;
        }
        else if (initialRabbits < MID_HIGH_RABBITS_T1)
        {
            return 5;
        }
        else if (initialRabbits < HIGH_RABBITS_T1)
        {
            return 4;
        }
        else
        {
            return 4;
        }
    }
    else
    {
        if (initialRabbits < LOW_RABBITS_T1)
        {
            return 0;
        }
        else if (initialRabbits < MID_LOW_RABBITS_T1)
        {
            return 9;
        }
        else if (initialRabbits < MID_HIGH_RABBITS_T1)
        {
            return 8;
        }
        else if (initialRabbits < HIGH_RABBITS_T1)
        {
            return 7;
        }
        else
        {
            return 5;
        }
    }
}

// Function to simulate rabbit reproduction
void simulateRabbitReproduction(IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y])
{
    srand(time(NULL));
    int previousRabbitCount = 0;
    #pragma omp parallel for reduction(+:previousRabbitCount)
    for (int i = 0; i < GRID_SIZE_X; i++)
    {
        int childRabbits = (rand() % 4) + 4;
        for (int j = 0; j < GRID_SIZE_Y; j++)
        {
            previousRabbitCount += island[i][j].rabbits;
            for (int k = 0; k < previousRabbitCount / 2; k++)
            {
                int babyRabbits = caluclateRabbitLitterSize(island[i][j].vegetation, island[i][j].rabbits);
                island[i][j].rabbits += babyRabbits;
                island[i][j].rabbits += childRabbits;
            }
        }
    }
}

// Function to calculate the number of baby foxes based on the initial rabbit and fox population
int calculateFoxLitterSize(int initialRabbits, int initialFoxes)
{
    if (initialRabbits < LOW_RABBITS_FOX)
    {
        if (initialFoxes < LOW_FOXES)
        {
            return 0;
        }
        else if (initialFoxes < MID_LOW_FOXES)
        {
            return 2;
        }
        else if (initialFoxes < MID_HIGH_FOXES)
        {
            return 2;
        }
        else if (initialFoxes < HIGH_FOXES)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (initialRabbits < MID_RABBITS_FOX)
    {
        if (initialFoxes < LOW_FOXES)
        {
            return 0;
        }
        else if (initialFoxes < MID_LOW_FOXES)
        {
            return 3;
        }
        else if (initialFoxes < MID_HIGH_FOXES)
        {
            return 3;
        }
        else if (initialFoxes < HIGH_FOXES)
        {
            return 2;
        }
        else
        {
            return 1;
        }
    }
    else if (initialRabbits < HIGH_RABBITS_FOX)
    {
        if (initialFoxes < LOW_FOXES)
        {
            return 0;
        }
        else if (initialFoxes < MID_LOW_FOXES)
        {
            return 4;
        }
        else if (initialFoxes < MID_HIGH_FOXES)
        {
            return 3;
        }
        else if (initialFoxes < HIGH_FOXES)
        {
            return 3;
        }
        else
        {
            return 2;
        }
    }
    else
    {
        if (initialFoxes < LOW_FOXES)
        {
            return 0;
        }
        else if (initialFoxes < MID_LOW_FOXES)
        {
            return 5;
        }
        else if (initialFoxes < MID_HIGH_FOXES)
        {
            return 4;
        }
        else if (initialFoxes < HIGH_FOXES)
        {
            return 3;
        }
        else
        {
            return 3;
        }
    }
}

// Function to simulate fox reproduction
void simulateFoxReproduction(IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y])
{
    int previousFoxCount = 0;
    #pragma omp parallel for reduction(+:previousFoxCount)
    for (int i = 0; i < GRID_SIZE_X; i++)
    {
        for (int j = 0; j < GRID_SIZE_Y; j++)
        {
            if (island[i][j].foxes > 2) island[i][j].foxes += 3;
            previousFoxCount += island[i][j].foxes;
            for (int k = 0; k < previousFoxCount / 2; k++)
            {
                int foxKits = calculateFoxLitterSize(island[i][j].rabbits, island[i][j].foxes);
                island[i][j].foxes += foxKits;
            }
        }
    }
}

// Function to determine if a fox eats a rabbit
int determineFoxEat(IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y], Position foxPosition)
{
    int x = foxPosition.x;
    int y = foxPosition.y;

    int eats = 0;

    IslandSquare square = island[x][y];

    if (square.rabbits > 0) {
        eats = (rand() % 7) + 1;
        if (square.vegetation < 0.6) {
            if (eats <= 4) {
                return 1;
            } else {
                return 0;
            }
        } else {
            if (eats <= 2) {
                return 1;
            } else {
                return 0;
            }
        }
    }
    return 0;
}

// Death and births
int simulateRabbitDeaths(IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y], int rabbitAgeSum)
{
    // seed random
    srand(time(NULL));
    int totalRabbits = 0;
    #pragma omp parallel for reduction(+:totalRabbits)
    for (int x = 0; x < GRID_SIZE_X; x++)
    {
        for (int y = 0; y < GRID_SIZE_Y; y++)
        {
            IslandSquare square = island[x][y];
            island[x][y].vegetation -= square.rabbits * 0.001;
            if (island[x][y].vegetation < 0)
            {
                int deadRabbits = (int)(-island[x][y].vegetation / 0.001);
                if (deadRabbits > island[x][y].rabbits)
                {
                    deadRabbits = island[x][y].rabbits;
                }
                island[x][y].rabbits -= deadRabbits;
                island[x][y].vegetation = 0;
            }
            totalRabbits += island[x][y].rabbits;
        }
    }
    if (totalRabbits > 0) {
        float rabbitAgeAverage = (float)rabbitAgeSum / totalRabbits;
        for (int x = 0; x < GRID_SIZE_X; x++)
        {
            for (int y = 0; y < GRID_SIZE_Y; y++)
            {
                island[x][y].rabbits -= ((rand() % 3) + 4);
                IslandSquare square = island[x][y];
                if (square.vegetation < 0.15 && rabbitAgeAverage > 3)
                {
                    int rabbitsToKill = (int)(square.rabbits * 0.1);
                    island[x][y].rabbits -= rabbitsToKill;
                } else if (square.vegetation < 0.25 && rabbitAgeAverage > 6)
                {
                    int rabbitsToKill = (int)(square.rabbits * 0.1);
                    island[x][y].rabbits -= rabbitsToKill;
                } else if (square.vegetation < 0.3 && rabbitAgeAverage > 12)
                {
                    int rabbitsToKill = (int)(square.rabbits * 0.1);
                    island[x][y].rabbits -= rabbitsToKill;
                } else if (square.vegetation >= 0.35 && rabbitAgeAverage > 18)
                {
                    int rabbitsToKill = (int)(square.rabbits * 0.1);
                    island[x][y].rabbits -= rabbitsToKill;
                }
                if (island[x][y].rabbits < 0)
                {
                    island[x][y].rabbits = 0;
                }
            }
        }
    }
    return rabbitAgeSum;
}

// Function to simulate fox deaths
void updateVegetation(IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y]) {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < GRID_SIZE_X; i++) {
        for (int j = 0; j < GRID_SIZE_Y; j++) { 
            // Formula
            double vegetationChange = (island[i][j].vegetation * 1.1) - (0.001 * island[i][j].rabbits);
            if (vegetationChange < 0) {
                vegetationChange = 0;
            }
            island[i][j].vegetation += 0.1;
            if (island[i][j].vegetation > 0.8) {
                island[i][j].vegetation = 0.8;
            }
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

// Function to check water edge
int isWaterEdge(Position position) {
    if (position.x == 0 || position.x == GRID_SIZE_X - 1 || position.y == 0 || position.y == GRID_SIZE_Y - 1) {
        return 1;
    }
    return 0;
}

// Function to migrate rabbits
void migrateRabbits(IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y], Position position) {
    int x = position.x;
    int y = position.y;
    int tempRabbits[GRID_SIZE_X][GRID_SIZE_Y];

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < GRID_SIZE_X; i++) {
        for (int j = 0; j < GRID_SIZE_Y; j++) {
            tempRabbits[i][j] = island[i][j].rabbits;
        }
    }
    int totalPopulation = 0;
    #pragma omp parallel for reduction(+:totalPopulation)
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            Position newPosition = {x + dx, y + dy};
            if ((dx == 0 && dy == 0) || isWaterEdge(newPosition)) {
                continue;
            }
            totalPopulation += island[x + dx][y + dy].rabbits;
        }
    }
    // Check if total population is zero and skip migration if total population is zero
    if (totalPopulation == 0) {
        return;
    }
    #pragma omp parallel for collapse(2)
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            Position newPosition = {x + dx, y + dy};
            if ((dx == 0 && dy == 0) || isWaterEdge(newPosition)) {
                continue;
            }
            // Calculate migration count based on relative population
            int migrationCount = island[x][y].rabbits * island[x + dx][y + dy].rabbits / totalPopulation;
            tempRabbits[x + dx][y + dy] += migrationCount;
            tempRabbits[x][y] -= migrationCount;
        }
    }
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < GRID_SIZE_X; i++) {
        for (int j = 0; j < GRID_SIZE_Y; j++) {
            island[i][j].rabbits = tempRabbits[i][j];
        }
    }
}

// Function to migrate foxes to other boxes
void migrateFoxes(IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y], Position position) {
    int x = position.x;
    int y = position.y;
    int tempFoxes[GRID_SIZE_X][GRID_SIZE_Y];

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < GRID_SIZE_X; i++) {
        for (int j = 0; j < GRID_SIZE_Y; j++) {
            tempFoxes[i][j] = island[i][j].foxes;
        }
    }
    int totalPopulation = 0;
    #pragma omp parallel for reduction(+:totalPopulation)
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            Position newPosition = {x + dx, y + dy};
            if ((dx == 0 && dy == 0) || isWaterEdge(newPosition)) {
                continue;
            }
            totalPopulation += island[x + dx][y + dy].foxes;
        }
    }
    if (totalPopulation == 0) {
        return;
    }
    #pragma omp parallel for collapse(2)
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            Position newPosition = {x + dx, y + dy};
            if ((dx == 0 && dy == 0) || isWaterEdge(newPosition)) {
                continue;
            }
            // Calculate migration count based on relative population
            int migrationCount = island[x][y].foxes * island[x + dx][y + dy].foxes / totalPopulation;
            tempFoxes[x + dx][y + dy] += migrationCount;
            tempFoxes[x][y] -= migrationCount;
        }
    }
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < GRID_SIZE_X; i++) {
        for (int j = 0; j < GRID_SIZE_Y; j++) {
            island[i][j].foxes = tempFoxes[i][j];
        }
    }
}

// Function to simulate all migration
void simulateMigration(IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y]) {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < GRID_SIZE_X; i++) {
        for (int j = 0; j < GRID_SIZE_Y; j++) {
            Position position = {i, j};
            if (isWaterEdge(position)) {
                continue;
            }
            migrateRabbits(island, position);
            migrateFoxes(island, position);
        }   
    }  
}

void simulateFoxDeaths(IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y], int foxAgeSum) {
    int totalFoxes = 0;

    // Parallelize the outer loops to distribute workload across multiple threads
    #pragma omp parallel for collapse(2) reduction(+:totalFoxes)
    for (int i = 0; i < GRID_SIZE_X; i++) {
        for (int j = 0; j < GRID_SIZE_Y; j++) {
            double naturalDeathChance = 0.1; // 10% chance of natural death
            
            int localTotalFoxes = 0;

            // Determine if each fox eats a rabbit
            #pragma omp parallel for reduction(+:localTotalFoxes)
            for (int fox = 0; fox < island[i][j].foxes; fox++) {
                int eatsRabbit = determineFoxEat(island, (Position){i, j});

                // Generate a random number to determine if a fox dies due to natural causes
                double naturalDeathRandom = (double)rand() / 100;
                if (naturalDeathRandom < naturalDeathChance) {
                    // Fox dies due to natural causes
                    #pragma omp atomic
                    island[i][j].foxes--;
                    if (island[i][j].foxes < 0) {
                        island[i][j].foxes = 0;
                    }
                }

                // Generate a random number to determine if a fox dies due to lack of food
                if (island[i][j].foxes > 0) {
                    if (eatsRabbit) {
                        // Fox eats a rabbit
                        #pragma omp atomic
                        island[i][j].rabbits--;
                        if (island[i][j].rabbits < 0) {
                            island[i][j].rabbits = 0;
                        }
                    } else {
                        // Fox doesn't eat a rabbit, check if it dies due to starvation
                        double starvationDeathRandom = (double)rand() / 100;
                        if (starvationDeathRandom < 0.1) { // 10% chance of starvation death
                            // Fox dies due to starvation
                            #pragma omp atomic
                            island[i][j].foxes--;
                            if (island[i][j].foxes < 0) {
                                island[i][j].foxes = 0;
                            }
                        }
                    }
                }
                localTotalFoxes++;
            }

            // Update totalFoxes using reduction clause
            totalFoxes += localTotalFoxes;

            // Apply additional fox death logic
            island[i][j].foxes -= 6;
            if (island[i][j].foxes < 0) {
                island[i][j].foxes = 0;
            }
        }
    }

    // Apply additional fox death logic based on foxAgeSum
    if (foxAgeSum > 0) {
        #pragma omp parallel for collapse(2)
        for (int i = 0; i < GRID_SIZE_X; i++) {
            for (int j = 0; j < GRID_SIZE_Y; j++) {
                IslandSquare square = island[i][j];
                int foxAgeAverage = foxAgeSum / totalFoxes;
                if (foxAgeAverage > 4) {
                    int foxesToKill = (int)(square.foxes * 0.1);
                    #pragma omp atomic
                    island[i][j].foxes -= foxesToKill;
                }
            }
        }
    }
}
