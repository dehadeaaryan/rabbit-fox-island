#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rabbitfox.h"

// Island grid
IslandSquare island[GRID_SIZE_X][GRID_SIZE_Y];

int main()
{
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
    simulateIsland(120); // Simulate the island for one month

    return 0;
}

// Function to initialize the island with initial population values and vegetation levels
void initializeIsland(int caseNumber)
{
    int success = 1;
    // #pragma omp parallel for collapse(2) shared(island, caseNumber)
    for (int i = 0; i < GRID_SIZE_X; i++)
    {
        for (int j = 0; j < GRID_SIZE_Y; j++)
        {
            switch (caseNumber)
            {
            case 1:
                island[i][j].rabbits = 100;
                island[i][j].foxes = 2;
                island[i][j].vegetation = 1.0;
                break;
            case 2:
                if (i == GRID_SIZE_X - 1 && j == GRID_SIZE_Y - 1)
                {
                    island[i][j].rabbits = 800;
                }
                else
                {
                    island[i][j].rabbits = 10;
                }
                if (i == GRID_SIZE_X - 1 && j == GRID_SIZE_Y - 1)
                {
                    island[i][j].foxes = 20;
                }
                else
                {
                    island[i][j].foxes = 0;
                }
                island[i][j].vegetation = 0.3;
                break;
            case 3:
                island[i][j].rabbits = 2;
                island[i][j].foxes = 0;
                island[i][j].vegetation = 0.5;
                break;
            default:
                printf("Invalid case number.\n");
                success = 0; // Indicate failure
                break;
            }
        }
    }

    if (!success)
    {
        return; // Return outside the parallel region
    }
}

// Function to visualize the island grid
void visualizeIsland()
{
    for (int i = 0; i < GRID_SIZE_X; i++)
    {
        for (int j = 0; j < GRID_SIZE_Y; j++)
        {
            printf(" %.2f %d %d ", island[i][j].vegetation, island[i][j].foxes, island[i][j].rabbits);
        }
        printf("\n");
    }
}

// Simulation function
void simulateIsland(int months)
{
    // Open file for writing
    FILE *fp;
    fp = fopen("simulation_results.csv", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    // Write headers
    fprintf(fp, "Month,Vegetation,Foxes,Rabbits\n");

    int daysFor9Weeks = 7 * 9;
    int daysFor6Months = 30 * 6;
    int rabbitAgeSum = 0;
    int foxAgeSum = 0;

    for (int month = 0; month < months; month++)
    {
        // seed rand
        srand(time(NULL));
        fprintf(fp, "%d,", month + 1);
        for (int day = 0; day < MONTH_DAYS; day++)
        {
            int r = rand() % 10 + 4;
            for (int i = 0; i < GRID_SIZE_X; i++)
            {
                for (int j = 0; j < GRID_SIZE_Y; j++)
                {
                    rabbitAgeSum += island[i][j].rabbits;
                    island[i][j].rabbits += r;
                    foxAgeSum += island[i][j].foxes;
                    island[i][j].foxes += (r - 2);
                }
            }
            if ((day % daysFor9Weeks) == 0 && day != 0)
            {
                simulateRabbitReproduction(island);
            }
            if ((day % daysFor6Months) == 0 && day != 0)
            {
                simulateFoxReproduction(island);
            }
            int totalRabbits = 0;
            int totalFoxes = 0;
            for (int i = 0; i < GRID_SIZE_X; i++)
            {
                for (int j = 0; j < GRID_SIZE_Y; j++)
                {
                    totalRabbits += island[i][j].rabbits;
                    totalFoxes += island[i][j].foxes;
                }
            }
            fprintf(fp, "%d,%d,%f,", totalRabbits, totalFoxes, island[0][0].vegetation);
            rabbitAgeSum = simulateRabbitDeaths(island, rabbitAgeSum);
            simulateFoxDeaths(island, foxAgeSum);
            updateVegetation(island);
        }
        fprintf(fp, "\n");
    }

    // Close file
    fclose(fp);
}