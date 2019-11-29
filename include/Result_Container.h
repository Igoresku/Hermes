//
// Created by Igor Duric on 11/29/19.
//

#ifndef PATH_FINDING_RESULT_CONTAINER_H
#define PATH_FINDING_RESULT_CONTAINER_H

#include <pthread.h>
#include "RAII.h"

class Result_Container {
public:
    explicit Result_Container();

    void Deliver(void*);
    void* Collect();

    virtual ~Result_Container();
private:
    virtual void Acknowledge_Delivery();
    virtual void Acknowledge_Collection();
    virtual bool Collectible();

    virtual void Deliver_Result(void*);
    virtual void* Collect_Result();

    pthread_mutex_t mutex;
    pthread_cond_t ready;

    bool result_ready = false;
    void* result;
};


#endif //PATH_FINDING_RESULT_H
