//
// Created by Igor Duric on 11/22/19.
//

#ifndef PATH_FINDING_MAP_CREATOR_MASTER_H
#define PATH_FINDING_MAP_CREATOR_MASTER_H

#include "Worker.h"
#include "Map_Creation_Job.h"
#include "Invalid_Parameters.h"

#define MAX_MC_WORKERS_ALLOWED 2

class Map_Creator {
public: /// META
    static Map_Creator* Get_Instance();

private: /// META
    static Map_Creator* instance;

public:
    Map_Creator(const Map_Creator&) = delete;
    Map_Creator(Map_Creator&&) = delete;

    /** Request for the random map to be created with given parameters:
     * dimensions - how big is a single side of the map, ought be a power of abstraction_size
     * abstraction_size - a logarithm of dimensions, determines the size of abstraction chunk
     * obstacle_factor - rough estimation of how much of the terrain percent will be impassable in a certain way
     * max_agent_size - max rectangular size allowed for an agent on this map
     * RESULT: NONE */
    void Create_Map(int dimensions, int abstraction_size, float obstacle_factor, int max_agent_size) noexcept(false);

    ~Map_Creator();
protected:
    explicit Map_Creator(int = MAX_MC_WORKERS_ALLOWED);

private:
    Worker** workers;
    int worker_amount;
    Job_Queue* job_queue;

    pthread_mutex_t job_file_mutex;
};


#endif //PATH_FINDING_MAP_CREATOR_MASTER_H
