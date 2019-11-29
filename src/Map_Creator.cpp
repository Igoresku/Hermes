//
// Created by Igor Duric on 11/22/19.
//

#include "../include/Map_Creator.h"

Map_Creator::Map_Creator(int worker_amount) : Employer(worker_amount) {
    abstraction_sizes = new int[4];
    abstraction_sizes[0] = 16;
    abstraction_sizes[1] = 12;
    abstraction_sizes[2] = 8;
    abstraction_sizes[3] = 4;

    pthread_mutex_init(&job_file_mutex, nullptr);
} /// Map_Creator : END

void Map_Creator::Create_Map(int dimensions, double obstacle_factor, double water_cliff_factor) {
    int fitting_abstraction_size = 0;

    for (int i = 0; i < 4; i++) {
        int curr = abstraction_sizes[i];
        while (curr < dimensions)
            curr *= abstraction_sizes[i];

        if (curr == dimensions) {
            fitting_abstraction_size = abstraction_sizes[i];
            break;
        }
    } // for : i

    if ((dimensions < 0) || (fitting_abstraction_size == 0))
        throw Invalid_Parameters(dimensions);

    if ((obstacle_factor < 0.0) || (obstacle_factor > 100.0) || (water_cliff_factor < 0.0) || (water_cliff_factor > 100.0))
        throw Invalid_Parameters(obstacle_factor);

    Add_Job(new Map_Creation_Job(dimensions, obstacle_factor, water_cliff_factor, job_file_mutex));
} /// Create_Map : END

void Map_Creator::List_Maps() {
    std::ifstream f_file_names;

    {
        RAII scoped_key(&job_file_mutex);

        f_file_names.open("../maps/all_maps.txt");
        std::string iterator;
        while (std::getline(f_file_names, iterator))
            std::cout << iterator << '\n';

        f_file_names.close();
    }
} /// List_Maps : END

Map_Creator::~Map_Creator() {
    delete[] abstraction_sizes;

    pthread_mutex_destroy(&job_file_mutex);
} /// ~Map_Creator : END