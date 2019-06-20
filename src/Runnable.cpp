//
// Created by Igor Duric on 4/17/19.
//

#include "../include/Runnable.h"

void* Runnable::Stub(void* thiz) {
    auto runnable = (Runnable*) thiz;
    void* res = runnable->run();
    runnable->set_Done();
    return res;
} /// Stub : END

void Runnable::start() {
    pthread_create(&handler, nullptr, Runnable::Stub, (void*) this);
} /// start : END

Runnable::~Runnable() = default;
