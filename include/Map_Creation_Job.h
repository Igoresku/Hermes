//
// Created by Igor Duric on 11/25/19.
//

#ifndef PATH_FINDING_MAP_CREATION_JOB_H
#define PATH_FINDING_MAP_CREATION_JOB_H

#include <random>
#include <fstream>
#include <iostream>
#include <string>
#include "Job.h"
#include "RAII.h"
#include "../../../Git/PerlinNoise/PerlinNoise.hpp"


class Map_Creation_Job : public Job {
public:
    Map_Creation_Job(int, int, float, int, pthread_mutex_t&);

    void Do_Job() override;

    ~Map_Creation_Job() override;
private:
    int dimensions;
    int abstraction_size;
    float obstacle_factor;
    int max_agent_size;
    const std::string file_names;

    pthread_mutex_t mutex;
};


#endif //PATH_FINDING_MAP_CREATION_JOB_H
