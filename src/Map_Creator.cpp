//
// Created by Igor Duric on 4/19/19.
//

#include "../include/Map_Creator.h"


Map_Creator* Map_Creator::Factory(int dimensions, int abstraction_size, float obstacle_factor, int max_agent_size) {
    if ((dimensions % abstraction_size) || (dimensions < 0) || (dimensions < 0))
        throw Invalid_Parameters(dimensions, abstraction_size);

    if ((max_agent_size < 1) || (max_agent_size > 5))
        throw Invalid_Parameters(max_agent_size);

    if ((obstacle_factor < 0.0) || (obstacle_factor > 100.0))
        throw Invalid_Parameters(obstacle_factor);

    return new Map_Creator(dimensions, abstraction_size, obstacle_factor, max_agent_size);
}

Map_Creator::Map_Creator(int dimensions, int abstraction_size, float obstacle_factor, int max_agent_size)
    : dimensions(dimensions), abstraction_size(abstraction_size), obstacle_factor(obstacle_factor), max_agent_size(max_agent_size) {

}

void* Map_Creator::run() {
    int length = 100, filled = 0;
    int* x = new int[100];
    int* y = new int[100];
    // http://www.cplusplus.com/reference/random/
    std::default_random_engine engine;
    std::uniform_int_distribution<int> distribution(1, 100);
    auto roll_terrain = std::bind(distribution, engine);

    for (int i = 0; i < dimensions; i++) {
        for (int j = 0; j < dimensions; j++) {
            // i begin with a map that is all passable, and add "seeds" of obstacles as random noise on the map


        } // for : j
    } // for : i
    return nullptr;
}