#ifndef ISLAND_H
#define ISLAND_H

#include <vector>

struct Square {
    int rabbits;
    int foxes;
    float vegetation;
};

class Island {
public:
    Island(int size);
    ~Island();

    void initialize(int initial_rabbits, int initial_foxes, float initial_vegetation);
    void simulate(int num_years);

private:
    int size_;
    std::vector<std::vector<Square>> grid_;

    float calculateVegetation(int x, int y, int num_rabbits);
    void updatePopulation(int x, int y);
    void handleMigration();
    void handleBirths();
    void handleDeaths();
};

#endif // ISLAND_H
