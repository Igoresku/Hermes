//
// Created by Igor Duric on 11/25/19.
//

#include "../include/Map_Creation_Job.h"


Map_Creation_Job::Map_Creation_Job(int dimensions, int abstraction_size, float obstacle_factor, int max_agent_size, pthread_mutex_t& mutex)
        : dimensions(dimensions), abstraction_size(abstraction_size), obstacle_factor(obstacle_factor), max_agent_size(max_agent_size),
        mutex(mutex) {}

void Map_Creation_Job::Do_Job() {
    siv::PerlinNoise perlin_noise;
    std::ifstream f_file_names;
    std::ofstream out_file;
    std::string makeshift_name = std::to_string(dimensions) + "_" + std::to_string(abstraction_size) + "_"
                                 + std::to_string(obstacle_factor) + "_" + std::to_string(max_agent_size);

    // TODO: rework this to a C++11 standard random engine
    srand (static_cast <unsigned> (time(0)));
    float frequency = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 64.0));

    {
        RAII raii(&mutex);

        f_file_names.open(file_names);
        std::string iterator;
        int file_number = 0;
        while (std::getline(f_file_names, iterator)) {
            int i = 0;
            for (; i <= makeshift_name.length(); i++) {
                if (iterator[i] != makeshift_name[i])
                    break;
            }

            if (i == makeshift_name.length() + 1)
                file_number++;
        }
        f_file_names.close();
        makeshift_name = makeshift_name + "_" + std::to_string(file_number);

        out_file.open(file_names, std::ios_base::app);
        out_file << makeshift_name << '\n';
        out_file.close();
    }

    makeshift_name = "../maps/" + makeshift_name + ".txt";
    out_file.open(makeshift_name);
    out_file << dimensions << '\n' << abstraction_size << '\n' << max_agent_size << '\n';
    obstacle_factor /= 100;
    for (int i = 0; i < dimensions; i++) {
        for (int j = 0; j < dimensions; j++) {
            double noise = perlin_noise.octaveNoise(i / frequency, j / frequency, 8);

            if (noise >= obstacle_factor) {
                if (noise >= obstacle_factor / 2)
                    out_file << '^';
                else
                    out_file << '~';
            } else
                out_file << '_';

        } // for : j

        out_file << '\n';
    } // for : i

    out_file.close();
} /// Do_Job : END

Map_Creation_Job::~Map_Creation_Job() = default;