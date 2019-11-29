//
// Created by Igor Duric on 11/29/19.
//

#include "../include/Result.h"

Result::Result() {
    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&ready, nullptr);
} /// Result : END

void Result::Deliver_Result(void* result) {
    RAII scoped_key(&mutex);

    this->result = result;
    result_ready = true;
    pthread_cond_broadcast(&ready);
} /// Deliver_Result : END

void* Result::Collect_Result() {
    RAII raii(&mutex);

    while (!result_ready)
        pthread_cond_wait(&ready, &mutex);
    return result;
} /// Collect_Result : END

Result::~Result() {
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&ready);
} /// ~Result : END