//
// Created by Igor Duric on 11/25/19.
//

#ifndef PATH_FINDING_JOB_H
#define PATH_FINDING_JOB_H

#include "Result.h"

class Job {
public:
    explicit Job(Result* = nullptr);

    virtual void Do_Job() = 0;

    virtual ~Job();
private:
    Result* result_container;
};


#endif //PATH_FINDING_JOB_H
