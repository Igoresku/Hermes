//
// Created by Igor Duric on 11/25/19.
//

#ifndef PATH_FINDING_JOB_H
#define PATH_FINDING_JOB_H

class Job {
public:
    explicit Job() = default;

    virtual void Do_Job() = 0;

    virtual ~Job();
};


#endif //PATH_FINDING_JOB_H
