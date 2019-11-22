//
// Created by Igor Duric on 4/19/19.
//

#include "../include/Map_Creator_Worker.h"

Map_Creator_Worker::Map_Creator_Worker(int dimensions, int abstraction_size, float obstacle_factor, int max_agent_size)
    : dimensions(dimensions), abstraction_size(abstraction_size), obstacle_factor(obstacle_factor), max_agent_size(max_agent_size),
    file_names("../maps/file_names.txt") {
    sem_init(&mutex, 0 , 1);
}

void* Map_Creator_Worker::run() {
    siv::PerlinNoise perlin_noise;
    std::ifstream f_file_names;
    std::ofstream out_file;
    std::string makeshift_name = std::to_string(dimensions) + "_" + std::to_string(abstraction_size) + "_"
            + std::to_string(obstacle_factor) + "_" + std::to_string(max_agent_size);

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
    sem_wait(&mutex); {
        out_file.open(file_names, std::ios_base::app);
        out_file << makeshift_name << '\n';
        out_file.close();
    } sem_post(&mutex);

    makeshift_name = "../maps/" + makeshift_name + ".txt";
    out_file.open(makeshift_name);
    out_file << dimensions << '\n' << abstraction_size << '\n' << max_agent_size << '\n';
    obstacle_factor /= 100;
    for (int i = 0; i < dimensions; i++) {
        for (int j = 0; j < dimensions; j++) {
            double rand = perlin_noise.octaveNoise(i / 32.0, j / 32.0, 8);

            if (rand >= obstacle_factor) {
                if (rand > 0.5)
                    out_file << '^';
                else
                    out_file << '~';
            } else
                out_file << '_';

        } // for : j

        out_file << '\n';
    } // for : i

    out_file.close();
    return nullptr;
} /// run : END