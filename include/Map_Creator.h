//
// Created by Igor Duric on 11/22/19.
//

#ifndef PATH_FINDING_MAP_CREATOR_MASTER_H
#define PATH_FINDING_MAP_CREATOR_MASTER_H

#include <stack>
#include "Map_Creator_Worker.h"
#include "Raise_Finished.h"

#define MAX_MC_WORKERS_ALLOWED 2

class Map_Creator : public Runnable {
public: // Meta
    static Map_Creator* Get_Instance();

private: // Meta
    static Map_Creator* instance;

    class Worker_List_E {
    public:
        explicit Worker_List_E(Map_Creator_Worker* payload, Worker_List_E* next = nullptr) : payload(payload), next(next) {};
        Map_Creator_Worker* payload;
        Worker_List_E* next;
    };

public:
    Map_Creator(const Map_Creator&) = delete;
    Map_Creator(Map_Creator&&) = delete;
    explicit Map_Creator();

    /** Request for the random map to be created with given parameters:
     * dimensions - how big is a single side of the map, ought be a power of abstraction_size
     * abstraction_size - a logarithm of dimensions, determines the size of abstraction chunk
     * obstacle_factor - rough estimation of how much of the terrain percent will be impassable in a certain way
     * max_agent_size - max rectangular size allowed for an agent on this map
     * RESULT: NONE */
    void Create_Map(int dimensions, int abstraction_size, float obstacle_factor, int max_agent_size) noexcept(false);

    void* run() override;

    ~Map_Creator() override;
private:
    bool end = false;

    Map_Creator_Worker** workers;
    std::stack<int>* finished_workers;
    Worker_List_E* head_waiting = nullptr;
    Worker_List_E* tail_waiting = nullptr;

    /// Used for mutual exclusion on thread creation, starting and cleanup
    sem_t mutex;
    /// Used for mutual exclusion on thread reporting when its done upon the stack of indexes
    sem_t workers_done_mutex;
    /// Amount of workers that have finished their work and are waiting to be cleaned up at the moment
    sem_t worker_finished;
    /// Given to worker threads for them to synchronize on a shared file
    sem_t worker_file_mutex;
};


#endif //PATH_FINDING_MAP_CREATOR_MASTER_H
