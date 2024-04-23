#include "island.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Island::Island(int size) : size_(size) {
    // Initialize random seed
    srand(time(nullptr));

    // Initialize the grid with empty squares
    grid_.resize(size_);
    for (int i = 0; i < size_; ++i) {
        grid_[i].resize(size_);
        for (int j = 0; j < size_; ++j) {
            grid_[i][j].rabbits = 0;
            grid_[i][j].foxes = 0;
            grid_[i][j].vegetation = 0.0f;
        }
    }
}

Island::~Island() {}

void Island::initialize(int initial_rabbits, int initial_foxes, float initial_vegetation) {
    // Initialize each square with initial population and vegetation
    for (int i = 0; i < size_; ++i) {
        for (int j = 0; j < size_; ++j) {
            grid_[i][j].rabbits = initial_rabbits;
            grid_[i][j].foxes = initial_foxes;
            grid_[i][j].vegetation = initial_vegetation;
        }
    }
}

void Island::simulate(int num_years) {
    for (int year = 0; year < num_years; ++year) {
        // Simulate each day in the year
        for (int day = 0; day < 365; ++day) {
            // Update vegetation levels
            // Update populations based on births, deaths, migration, etc.
            // Handle births, deaths, migration, etc.
            // Print or save results as required
        }
    }
}

float Island::calculateVegetation(int x, int y, int num_rabbits) {
    // Calculate vegetation level based on growth/consumption formula
    // Return updated vegetation level
    return 0.0f; // Placeholder, replace with actual calculation
}

void Island::updatePopulation(int x, int y) {
    // Update population in a square based on births, deaths, etc.
}

void Island::handleMigration() {
    // Handle migration of rabbits and foxes
}

void Island::handleBirths() {
    // Handle births of rabbits and foxes
}

void Island::handleDeaths() {
    // Handle deaths of rabbits and foxes
}
