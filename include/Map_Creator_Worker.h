//
// Created by Igor Duric on 4/19/19.
//

#ifndef PATH_FINDING_MAP_CREATOR_H
#define PATH_FINDING_MAP_CREATOR_H

#include <random>
#include <fstream>
#include <iostream>
#include "Runnable.h"
#include "Invalid_Parameters.h"
#include "../../../Git/PerlinNoise/PerlinNoise.hpp"

class Map_Creator_Worker: public Runnable {
public:
    Map_Creator_Worker(int, int, float, int, sem_t);

    ~Map_Creator_Worker() override { while(!is_Done()); };
protected:
    void* run() override;

private:
    int dimensions;
    int abstraction_size;
    float obstacle_factor;
    int max_agent_size;
    const std::string file_names;

    /// Used for mutual exclusion on the file that contains all map names that exist
    sem_t mutex;
};

#endif //PATH_FINDING_MAP_CREATOR_H
