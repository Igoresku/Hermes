//
// Created by Igor Duric on 11/27/19.
//

#include "../include/Employer.h"

Employer::Employer(int worker_amount, Job_Queue* job_queue) : worker_amount(worker_amount), job_queue(job_queue), shared(true) {
    Initialize_Workers();
} /// Employer : END

Employer::Employer(int worker_amount) : worker_amount(worker_amount), job_queue(new Job_Queue()), shared(false) {
    Initialize_Workers();
} /// Employer : END

void Employer::Add_Job(Job* job) {
    job_queue->Add_Job(job);
} /// Add_Job : END

void Employer::Initialize_Workers() {
    workers = new Worker*[worker_amount];
    for (int i = 0; i < worker_amount; i++) {
        workers[i] = new Worker(job_queue);
        workers[i]->start();
    }
} /// Initialize_Workers : END

Employer::~Employer() {
    if (!shared)
        delete job_queue;

    for (int i = 0; i < worker_amount; i++)
        delete workers[i];

    delete[] workers;
} /// ~Employer : END