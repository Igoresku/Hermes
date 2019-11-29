//
// Created by Igor Duric on 11/29/19.
//

#ifndef PATH_FINDING_RESULT_H
#define PATH_FINDING_RESULT_H

#include <pthread.h>
#include "RAII.h"

class Result {
    explicit Result();

    virtual void Deliver_Result(void*);
    virtual void* Collect_Result();

    virtual ~Result() = 0;
private:
    pthread_mutex_t mutex;
    pthread_cond_t ready;
    bool result_ready = false;

    void* result;
};


#endif //PATH_FINDING_RESULT_H
