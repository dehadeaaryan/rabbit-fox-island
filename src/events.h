#ifndef EVENTS_H
#define EVENTS_H

#include "constants.h"
#include "structs.h"

int caluclateRabbitLitterSize(double vegetation, int initialRabbits);
int calculateFoxLitterSize(int initialRabbits, int initialFoxes);
void simulateFoxDeaths(IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y]);

#endif