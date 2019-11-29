//
// Created by Igor Duric on 11/25/19.
//

#ifndef PATH_FINDING_JOB_QUEUE_H
#define PATH_FINDING_JOB_QUEUE_H

#include <pthread.h>
#include "Job.h"
#include "RAII.h"

class Job_Queue {
private: /// META
    class Job_List_Element {
    public:
        explicit Job_List_Element(Job* payload, Job_List_Element* next = nullptr): payload(payload), next(next) {};
        Job* payload;
        Job_List_Element* next;
    };

public:
    Job_Queue();

    void Add_Job(Job*);
    Job* Get_Job();

    ~Job_Queue();
private:
    Job_List_Element* head = nullptr;
    Job_List_Element* tail = nullptr;

    pthread_mutex_t mutex;
    pthread_cond_t not_empty;
};


#endif //PATH_FINDING_JOB_QUEUE_H
