#ifndef EVENTS_H
#define EVENTS_H

#include "constants.h"
#include "structs.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int caluclateRabbitLitterSize(double vegetation, int initialRabbits);
int calculateFoxLitterSize(int initialRabbits, int initialFoxes);
int determineFoxEat(IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y], Position foxPosition);
void simulateRabbitDeath(IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y], int *ages);
void updateVegetation(IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y]);
int isWaterEdge(Position position);
void migrateRabbits(IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y], Position position);
void migrateFoxes(IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y], Position position);
void simulateMigration(IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y]);

#endif