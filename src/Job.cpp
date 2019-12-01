//
// Created by Igor Duric on 11/25/19.
//

#include "../include/Job.h"

Job::Job(Result_Queue* result_queue) : result_queue(result_queue) {};

Job::~Job() = default;