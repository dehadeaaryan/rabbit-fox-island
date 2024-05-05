#include "events.h"

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
}

void simulateRabbitDeath(IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y], int *ages)
{
    for (int x = 0; x < GRID_SIZE_X; x++)
    {
        for (int y = 0; y < GRID_SIZE_Y; y++)
        {
            IslandSquare square = island[x][y];
            island[x][y].vegetation -= square.rabbits * 0.001;
            if (island[x][y].vegetation < 0)
            {
                int deadRabbits = (int)(-island[x][y].vegetation / 0.001);
                island[x][y].rabbits -= deadRabbits;
                island[x][y].vegetation = 0;
            }
        }
    }
}

// Vegetation Update function
void updateVegetation(IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y]) {
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

int isWaterEdge(Position position) {
    if (position.x == 0 || position.x == GRID_SIZE_X - 1 || position.y == 0 || position.y == GRID_SIZE_Y - 1) {
        return 1;
    }
    return 0;
}

void migrateRabbits(IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y], Position position) {
    int x = position.x;
    int y = position.y;
    int tempRabbits[GRID_SIZE_X][GRID_SIZE_Y];

    for (int i = 0; i < GRID_SIZE_X; i++) {
        for (int j = 0; j < GRID_SIZE_Y; j++) {
            tempRabbits[i][j] = island[i][j].rabbits;
        }
    }
    // Iterate over each neighboring square
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            Position newPosition = {x + dx, y + dy};
            if ((dx == 0 && dy == 0) || isWaterEdge(newPosition)) {
                continue;
            }
            int migrationCount = rand() % (island[x][y].rabbits + 1);
            tempRabbits[x + dx][y + dy] += migrationCount;
            tempRabbits[x][y] -= migrationCount;
        }
    }
    for (int i = 0; i < GRID_SIZE_X; i++) {
        for (int j = 0; j < GRID_SIZE_Y; j++) {
            island[i][j].rabbits = tempRabbits[i][j];
        }
    }
}

void migrateFoxes(IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y], Position position) {
    int x = position.x;
    int y = position.y;
    int tempFoxes[GRID_SIZE_X][GRID_SIZE_Y];

    for (int i = 0; i < GRID_SIZE_X; i++) {
        for (int j = 0; j < GRID_SIZE_Y; j++) {
            tempFoxes[i][j] = island[i][j].foxes;
        }
    }

    // Iterate over each neighboring square
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            Position newPosition = {x + dx, y + dy};
            if ((dx == 0 && dy == 0) || isWaterEdge(newPosition)) {
                continue;
            }
            int migrationCount = rand() % (island[x][y].foxes + 1);
            tempFoxes[x + dx][y + dy] += migrationCount;
            tempFoxes[x][y] -= migrationCount;
        }
    }
    for (int i = 0; i < GRID_SIZE_X; i++) {
        for (int j = 0; j < GRID_SIZE_Y; j++) {
            island[i][j].foxes = tempFoxes[i][j];
        }
    }
}

void simulateMigration(IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y]) {
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

// tester
int main() {
    IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y];
    int ages[INITIAL_RABBITS] = {0};
    simulateRabbitDeath(island, ages);
}