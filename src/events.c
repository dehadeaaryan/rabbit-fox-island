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

void simulateFoxDeaths(IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y])
{
    for (int i = 0; i < GRID_SIZE_X; i++)
    {
        for (int j = 0; j < GRID_SIZE_Y; j++)
        {
            IslandSquare square = island[i][j];
            
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