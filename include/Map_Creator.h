//
// Created by Igor Duric on 11/22/19.
//

#ifndef PATH_FINDING_MAP_CREATOR_MASTER_H
#define PATH_FINDING_MAP_CREATOR_MASTER_H

#include "Employer.h"
#include "Map_Creation_Job.h"
#include "Invalid_Parameters.h"

class Map_Creator : public Employer{
public:
    explicit Map_Creator(int = 1);

    Map_Creator(const Map_Creator&) = delete;
    Map_Creator(Map_Creator&&) = delete;

    /** Request for the random map to be created with given parameters:
     * dimensions - how big is a single side of the map, ought be a power of 4, 8, 12 or 16
     * obstacle_factor - rough estimation of how much of the terrain will be impassable, [0.0, 100.0]
     * water_cliff_factor - rough estimation of how much of impassable terrain is water/cliff, [0.0, 100.0]
     * RESULT: NONE */
    void Create_Map(int dimensions, double obstacle_factor, double water_cliff_factor) noexcept(false);
    void List_Maps();
    std::ofstream Choose_Map(std::string);

    ~Map_Creator() override;
private:
    int* abstraction_sizes;

    pthread_mutex_t job_file_mutex;
};


#endif //PATH_FINDING_MAP_CREATOR_MASTER_H
