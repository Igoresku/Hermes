//
// Created by Igor Duric on 11/25/19.
//

#include "../include/RAII.h"

RAII::RAII(pthread_mutex_t* mutex) : mutex(mutex) {
    pthread_mutex_lock(this->mutex);
}

RAII::~RAII() {
    pthread_mutex_unlock(this->mutex);
}