//
// Created by Igor Duric on 11/22/19.
//

#include "../include/Map_Creator.h"

Map_Creator* Map_Creator::instance = nullptr;

Map_Creator* Map_Creator::Get_Instance() {
    if (instance != nullptr)
        instance = new Map_Creator();

    return instance;
}

Map_Creator::Map_Creator() {
    sem_init(&mutex, 0, 1);
    sem_init(&workers_done_mutex, 0, 1);
    sem_init(&worker_finished, 0, 0);
    sem_init(&worker_file_mutex, 0, 1);

    workers = new Map_Creator_Worker*[MAX_MC_WORKERS_ALLOWED];
    for (int i = 0; i < MAX_MC_WORKERS_ALLOWED; i++)
        workers[i] = nullptr;

    finished_workers = new std::stack<int>;
}

void Map_Creator::Create_Map(int dimensions, int abstraction_size, float obstacle_factor, int max_agent_size) {

    if (end)
        return;

    if ((dimensions % abstraction_size) || (dimensions < 0) || (abstraction_size < 0))
        throw Invalid_Parameters(dimensions, abstraction_size);

    if ((max_agent_size < 1) || (max_agent_size > 5))
        throw Invalid_Parameters(max_agent_size);

    if ((obstacle_factor < 0.0) || (obstacle_factor > 100.0))
        throw Invalid_Parameters(obstacle_factor);

    sem_wait(&mutex); {
        int i;
        for (i = 0; i < MAX_MC_WORKERS_ALLOWED; i++) {
            if (workers[i] == nullptr)
                break;
        }

        if (i < MAX_MC_WORKERS_ALLOWED) {
            workers[i] = new Map_Creator_Worker(dimensions, abstraction_size, obstacle_factor, max_agent_size, worker_file_mutex);
            workers[i]->Add_PwD(new Raise_Finished(worker_finished, finished_workers, workers_done_mutex, i));
            workers[i]->start();
        } else {
            auto waiting_worker = new Worker_List_E
                    (new Map_Creator_Worker(dimensions, abstraction_size, obstacle_factor, max_agent_size, worker_file_mutex));

            if (head_waiting == nullptr)
                head_waiting = waiting_worker;
            else
                tail_waiting->next = waiting_worker;
            tail_waiting = waiting_worker;
        }
    } sem_post(&mutex);
} /// Create_Map : END

void* Map_Creator::run() {

   while (!end) {
       sem_wait(&worker_finished);
       sem_wait(&mutex); {
           int index_done;
           sem_wait(&workers_done_mutex); {
               index_done = finished_workers->top();
               finished_workers->pop();
           } sem_post(&workers_done_mutex);
           delete workers[index_done];

           if (head_waiting != nullptr) {
               auto new_worker = head_waiting->payload;
               new_worker->Add_PwD(new Raise_Finished(worker_finished, finished_workers, workers_done_mutex, index_done));
               workers[index_done] = new_worker;
               workers[index_done]->start();

               auto temp = head_waiting;
               head_waiting = head_waiting->next;
               if (head_waiting == nullptr)
                   tail_waiting = nullptr;
               delete temp;
           } else
               workers[index_done] = nullptr;

       } sem_post(&mutex);
   } // while : end

   return nullptr;
} /// run : END

Map_Creator::~Map_Creator() {
    end = true;
    while (!is_Done());

    auto iterator = head_waiting;
    Worker_List_E* scout;
    while (iterator != tail_waiting) {
        scout = iterator->next;
        delete iterator->payload;
        delete iterator;
        iterator = scout;
    }
    if (iterator != nullptr) {
        delete iterator->payload;
        delete iterator;
    }

    for (int i = 0; i < MAX_MC_WORKERS_ALLOWED; i++) {
        while (!workers[i]->is_Done());
        delete workers[i];
    }
    delete workers;
    delete finished_workers;

    sem_destroy(&mutex);
    sem_destroy(&workers_done_mutex);
    sem_destroy(&worker_finished);
    sem_destroy(&worker_file_mutex);
}