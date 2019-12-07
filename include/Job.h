//
// Created by Igor Duric on 11/25/19.
//

#ifndef PATH_FINDING_JOB_H
#define PATH_FINDING_JOB_H

#include "Product.h"

/** A task to be performed, inherit from this class to define a job
 * that can be placed in a queue and performed by some worker(?) thread */
class Job {
public:
    Job();

    virtual void Do_Job() = 0;

    virtual ~Job();
};


#endif //PATH_FINDING_JOB_H
