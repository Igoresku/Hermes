//
// Created by Igor Duric on 11/25/19.
//

#ifndef PATH_FINDING_WORKER_H
#define PATH_FINDING_WORKER_H

#include "Runnable.h"
#include "Job.h"
#include "Job_Queue.h"

class Worker : public Runnable {
public:
    explicit Worker(Job_Queue*);

    void* run() override;

    ~Worker() override;
private:
    bool stop = false;

    Job_Queue* job_queue;
    Job* job;
};


#endif //PATH_FINDING_WORKER_H
