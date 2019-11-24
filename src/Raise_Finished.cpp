//
// Created by Igor Duric on 11/23/19.
//

#include "../include/Raise_Finished.h"

Raise_Finished::Raise_Finished(sem_t signal, std::stack<int>* master, sem_t master_mutex, int index) : signal(signal),
    master(master), master_mutex(master_mutex), index(index) {};

void Raise_Finished::Perform_Action() {
    sem_wait(&master_mutex); {
        master->push(index);
    } sem_post(&master_mutex);
    sem_post(&signal);
}

Raise_Finished::~Raise_Finished() = default;