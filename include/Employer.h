//
// Created by Igor Duric on 11/27/19.
//

#ifndef PATH_FINDING_EMPLOYER_H
#define PATH_FINDING_EMPLOYER_H

#include "Worker.h"
#include "Job.h"

/** Employer is a class that is meant to be overloaded in conjunction with classes Job and
 * Job_Arguments (and optionally Job_Queue class), it will utilize a number of all-purpose
 * workers to perform requested jobs. Employers may share a Job_Queue between themselves,
 * using all their workers to do the jobs which may be of various types, however then
 * the programmer must ensure the destruction of the Job_Queue. When overloading, create
 *  a method that calls Add_Job(Job*) at its end, enabling throwing exceptions and
 * such, if arguments can be wrong. */
class Employer {
public:
    Employer(int, Job_Queue*);
    explicit Employer(int);

    // TODO: add this functionality
    // virtual void Create_Job(Job_Arguments*);

    virtual ~Employer() = 0;
protected:
    void Add_Job(Job*);
private:
    virtual void Initialize_Workers();

    Worker** workers;
    int worker_amount;
    Job_Queue* job_queue;

    bool shared;
};

#endif //PATH_FINDING_EMPLOYER_H
