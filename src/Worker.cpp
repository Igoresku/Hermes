//
// Created by Igor Duric on 11/25/19.
//

#include "../include/Worker.h"

Worker::Worker(Job_Queue* job_queue) : job_queue(job_queue) {}

void* Worker::run() {
    while (!stop) {
        cancellation_point();
        job = job_queue->Get_Job();
        job->Do_Job();
        delete job;
    }
} /// run : END

Worker::~Worker() {
    stop = true;
    while (!is_Done());
}