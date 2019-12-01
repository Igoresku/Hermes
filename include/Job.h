//
// Created by Igor Duric on 11/25/19.
//

#ifndef PATH_FINDING_JOB_H
#define PATH_FINDING_JOB_H

#include "Result_Queue.h"

/** */
class Job {
public:
    explicit Job(Result_Queue* = nullptr);

    virtual void Do_Job() = 0;

    virtual ~Job();
protected:
    Result_Queue* result_queue;
};


#endif //PATH_FINDING_JOB_H
