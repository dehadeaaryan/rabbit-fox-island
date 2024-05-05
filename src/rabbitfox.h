#ifndef RABBIT_FOX_ISLAND_H
#define RABBIT_FOX_ISLAND_H

#include "constants.h"
#include "structs.h"
#include "events.h"

void initialiseIsland(IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y]);
void visualiseIsland(IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y]);
void simulateIsland(IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y]);

#endif