//
// Created by Igor Duric on 4/17/19.
//

#include "../include/Runnable.h"

Runnable::~Runnable() = default;

void* Runnable::Stub(void* thiz) {
    auto runnable = (Runnable*) thiz;
    void* res = runnable->run();
    runnable->set_Done();
    return res;
}

void Runnable::start() {
    pthread_create(&handler, nullptr, Runnable::Stub, (void*) this);
}

