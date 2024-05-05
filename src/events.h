#ifndef EVENTS_H
#define EVENTS_H

#include "constants.h"
#include "structs.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int caluclateRabbitLitterSize(double vegetation, int initialRabbits);
void simulateRabbitReproduction(IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y]);
int calculateFoxLitterSize(int initialRabbits, int initialFoxes);
void simulateFoxReproduction(IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y]);
int determineFoxEat(IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y], Position foxPosition);
void simulateRabbitDeaths(IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y], int rabbitAgeSum);
void simulateFoxDeaths(IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y], int foxAgeSum);
void updateVegetation(IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y]);
int isWaterEdge(Position position);
void migrateRabbits(IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y], Position position);
void migrateFoxes(IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y], Position position);
void simulateMigration(IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y]);

#endif