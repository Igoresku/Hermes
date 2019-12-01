//
// Created by Igor Duric on 11/29/19.
//

#ifndef PATH_FINDING_RESULT_QUEUE_H
#define PATH_FINDING_RESULT_QUEUE_H

#include <pthread.h>
#include "RAII.h"

/** Contains results from a certain job(s), then waits to be consumed */
class Result_Queue {
private: /// META
    class Result_List_Element {
    public:
        explicit Result_List_Element(void* payload, Result_List_Element* next = nullptr) : payload(payload), next(next) {};
        void* payload;
        Result_List_Element* next;
    };

public:
    explicit Result_Queue();

    void Deliver(void*);
    void* Collect();

    virtual ~Result_Queue();
private:
    Result_List_Element* head = nullptr;
    Result_List_Element* tail = nullptr;

    pthread_mutex_t mutex;
    pthread_cond_t ready;
};


#endif //PATH_FINDING_RESULT_H
