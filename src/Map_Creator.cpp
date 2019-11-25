//
// Created by Igor Duric on 11/22/19.
//

#include "../include/Map_Creator.h"

Map_Creator* Map_Creator::instance = nullptr;

Map_Creator* Map_Creator::Get_Instance() {
    if (instance != nullptr)
        instance = new Map_Creator();

    return instance;
} /// Get_Instance : END

Map_Creator::Map_Creator(int worker_amount) : worker_amount(worker_amount) {
    job_queue = new Job_Queue();

    workers = new Worker*[worker_amount];
    for (int i = 0; i < worker_amount; i++) {
        workers[i] = new Worker(job_queue);
        workers[i]->start();
    }

    pthread_mutex_init(&job_file_mutex, nullptr);
} /// Map_Creator : END

void Map_Creator::Create_Map(int dimensions, int abstraction_size, float obstacle_factor, int max_agent_size) {

    if ((dimensions % abstraction_size) || (dimensions < 0) || (abstraction_size < 0))
        throw Invalid_Parameters(dimensions, abstraction_size);

    if ((max_agent_size < 1) || (max_agent_size > 4))
        throw Invalid_Parameters(max_agent_size);

    if ((obstacle_factor < 0.0) || (obstacle_factor > 100.0))
        throw Invalid_Parameters(obstacle_factor);

    job_queue->Add_Job(new Map_Creation_Job(dimensions, abstraction_size, obstacle_factor, max_agent_size, job_file_mutex));
} /// Create_Map : END

Map_Creator::~Map_Creator() {
    delete job_queue;

    for (int i = 0; i < worker_amount; i++)
        delete workers[i];
    delete[] workers;

    pthread_mutex_destroy(&job_file_mutex);
} /// ~Map_Creator : END