// Includes
#include <vector>
#include <iostream>
#include <string>

// Defines
#define DEATH_RATE 0.1

// Class
class Rabbit {
    public:
        // Constructors
        Rabbit();

        // Destructors
        ~Rabbit();

        // Functions
        void printRabbit();
        void killRabbit();
        
    private:
        // Variables
        int age;
        bool is_alive;
        // Functions
        void generateAge();
};