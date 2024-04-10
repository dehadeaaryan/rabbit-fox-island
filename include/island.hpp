// Includes
#include <vector>
#include <iostream>
#include <string>
#include <cmath>

// Defines
#define NUM_SQUARES 64

// Class
class Island {
    public:
        // Constructors
        Island();

        // Destructors
        ~Island();

        // Variables
        std::string name;

        // Functions
        void printIsland();
        
    private:
        // Variables
        std::vector<std::vector<char>> island;

        // Functions
        void generateIsland();
};