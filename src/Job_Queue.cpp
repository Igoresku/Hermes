//
// Created by Igor Duric on 11/25/19.
//

#include "../include/Job_Queue.h"

Job_Queue::Job_Queue() {
    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&not_empty, nullptr);
}

void Job_Queue::Add_Job(Job* job) {

    {
        RAII raii(&mutex);

        auto new_job = new Job_List_Element(job);
        if (head == nullptr)
            head = new_job;
        else
            tail->next = new_job;
        tail = new_job;
    }
    pthread_cond_broadcast(&not_empty);
} /// Add_Job : END

Job* Job_Queue::Get_Job() {
    RAII raii(&mutex);

    while (head == nullptr)
        pthread_cond_wait(&not_empty, &mutex);

    Job* job = head->payload;
    auto temp = head;
    head = head->next;
    if (head == nullptr)
        tail = nullptr;
    delete temp;

    return job;
} /// Get_Job : END

Job_Queue::~Job_Queue() {
    auto iterator = head;
    Job_List_Element* scout;

    while (iterator != tail) {
        scout = iterator->next;
        delete iterator->payload;
        delete iterator;
        iterator = scout;
    }
    if (iterator != nullptr) {
        delete iterator->payload;
        delete iterator;
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&not_empty);
} /// Job_Queue : END