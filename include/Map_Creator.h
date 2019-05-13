//
// Created by Igor Duric on 4/19/19.
//

#ifndef PATH_FINDING_MAP_CREATOR_H
#define PATH_FINDING_MAP_CREATOR_H

#include <random>
#include <fstream>
#include "Runnable.h"
#include "Invalid_Parameters.h"
#include "../../../Git/PerlinNoise/PerlinNoise.hpp"

class Map_Creator: public Runnable {
public: // Meta
    static Map_Creator* Factory(int = 262144, int = 8, float = 25.0, int = 3) noexcept(false);

public:
    Map_Creator(int, int, float, int);

    void* run() override;

private:
    int dimensions;
    int abstraction_size;
    float obstacle_factor;
    int max_agent_size;
    static const std::string file_names;
};

#endif //PATH_FINDING_MAP_CREATOR_H
