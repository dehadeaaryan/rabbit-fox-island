// Includes
#include "../include/island.hpp"

// Island Class
class Island {
    public: 
        Island() {
            generate_island();
        }

    private:
        std::vector<std::vector<char>> island = {};

        void generate_island() {
            // Add 64 squares to the island
            for (int i = 0; i < sqrt(NUM_SQUARES); i++) {
                std::vector<char> row;
                for (int j = 0; j < sqrt(NUM_SQUARES); j++) {
                    row.push_back(' ');
                }
                island.push_back(row);
            }
        }

        std::vector<std::vector<char>> island;
};