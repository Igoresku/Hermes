//
// Created by Igor Duric on 11/25/19.
//

#include "../include/Map_Creation_Job.h"


Map_Creation_Job::Map_Creation_Job(int dimensions, double obstacle_factor, double water_cliff_factor, pthread_mutex_t& mutex)
        : dimensions(dimensions), obstacle_factor(obstacle_factor), water_cliff_factor(water_cliff_factor), mutex(mutex) {}

void Map_Creation_Job::Do_Job() {
    siv::PerlinNoise perlin_noise;
    std::ifstream f_file_names;
    std::ofstream out_file;
    std::string makeshift_name = std::to_string(dimensions) + "_"
            + std::to_string(obstacle_factor) + "_" + std::to_string(water_cliff_factor);

    // TODO: rework this to a C++ standard random engine
    srand (static_cast <unsigned> (time(0)));
    float frequency = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 64.0));

    {
        RAII scoped_key(&mutex);

        f_file_names.open("../maps/all_maps.txt");
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
        } /// while : iterator
        f_file_names.close();
        makeshift_name = makeshift_name + "_" + std::to_string(file_number);

        out_file.open("../maps/all_maps.txt", std::ios_base::app);
        out_file << makeshift_name << '\n';
        out_file.close();
    }

    makeshift_name = "../maps/" + makeshift_name + ".txt";
    out_file.open(makeshift_name);
    out_file << dimensions << '\n';

    obstacle_factor /= 100;
    water_cliff_factor /= 100;
    Basic_Terrain_Type tile[2];
    Terrain terrain[2];
    int tile_done = 0;
    int terrain_done = 0;
    for (int i = 0; i < dimensions; i++) {
        for (int j = 0; j < dimensions; j++) {
            if (obstacle_factor > perlin_noise.octaveNoise( i / frequency, j / frequency, 8))
                tile[tile_done] = Basic_Terrain_Type::LAND;
            else {
                if (water_cliff_factor > perlin_noise.octaveNoise((i + dimensions) / frequency, j / frequency, 8))
                    tile[tile_done] = Basic_Terrain_Type::IMPASSABLE;
                else
                    tile[tile_done] = Basic_Terrain_Type::WATER;
            }

            tile_done = (tile_done + 1) % 2;
            if (tile_done == 0) {
                terrain[terrain_done] = Create_Terrain(tile[0], tile[1]);
                terrain_done = (terrain_done + 1) % 2;
                if (terrain_done == 0)
                    out_file << Pack_Terrain(terrain[0], terrain[1]);
            }
        } /// for : j

        out_file << '\n';
    } /// for : i

    out_file.close();
} /// Do_Job : END

Map_Creation_Job::~Map_Creation_Job() = default;