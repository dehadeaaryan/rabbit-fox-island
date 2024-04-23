#ifndef UTILS_H
#define UTILS_H

#include <cstdlib>

namespace utils {
    // Generate a random integer between min and max
    inline int randomInt(int min, int max) {
        return rand() % (max - min + 1) + min;
    }

    // Generate a random float between 0 and 1
    inline float randomFloat() {
        return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    }
}

#endif // UTILS_H
