//
// Created by Igor Duric on 11/25/19.
//

#ifndef PATH_FINDING_JOB_H
#define PATH_FINDING_JOB_H

#include "Result_Container.h"

class Job {
public:
    explicit Job(Result_Container* = nullptr);

    virtual void Do_Job() = 0;

    virtual ~Job();
protected:
    Result_Container* result_container;
};


#endif //PATH_FINDING_JOB_H
