//
// Created by Igor Duric on 11/27/19.
//

#ifndef PATH_FINDING_EMPLOYER_H
#define PATH_FINDING_EMPLOYER_H

#include "Worker.h"
#include "Job.h"

class Employer {
public:
    Employer(int, Job_Queue*);
    explicit Employer(int);

    virtual ~Employer();
protected:
    void Add_Job(Job*);
private:
    void Initialize_Workers();

    Worker** workers;
    int worker_amount;
    Job_Queue* job_queue;

    bool shared;
};


#endif //PATH_FINDING_EMPLOYER_H
