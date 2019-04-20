//
// Created by Igor Duric on 4/19/19.
//

#include "../include/Map_Creator.h"


Map_Creator* Map_Creator::Factory(int dimensions, int abstraction_size, int max_agent_size) {
    if ((dimensions % abstraction_size) || (dimensions < 0) || (dimensions < 0))
        throw Invalid_Parameters(dimensions, abstraction_size);

    if ((max_agent_size < 1) || (max_agent_size > 3))
        throw Invalid_Parameters(max_agent_size);

    return new Map_Creator(dimensions, abstraction_size, max_agent_size);
}

Map_Creator::Map_Creator(int dimensions, int abstraction_size, int max_agent_size)
    : dimensions(dimensions), abstraction_size(abstraction_size), max_agent_size(max_agent_size) {

}

void* Map_Creator::run() {

    return nullptr;
}