// includes
#include <iostream>
#include "../include/main.hpp"

void Main::printHelloWorld() {
    std::cout << "Hello World!" << std::endl;
}

// main function
int main() {
    // Createa an instance of main
    Main main;
    // Call the printHelloWorld function
    main.printHelloWorld();
    return 0;
}