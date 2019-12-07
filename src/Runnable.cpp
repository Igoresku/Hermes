//
// Created by Igor Duric on 4/17/19.
//

#include "../include/Runnable.h"

void* Runnable::Stub(void* me) {
    auto runnable = (Runnable*) me;
    void* res = runnable->run();
    runnable->set_Done();
    return res;
} /// Stub : END

Runnable::Runnable() = default;

void Runnable::start() {
    pthread_create(&handler, nullptr, Runnable::Stub, (void*) this);
} /// start : END

void Runnable::join(void* result) {
    pthread_join(handler, &result);
} /// join : END

void Runnable::detach() {
    pthread_detach(handler);
} /// detach : END

void Runnable::cancel() {
    pthread_cancel(handler);
} /// cancel : END

void Runnable::disable_cancel() {
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &state);
} /// set_uncancelable : END

void Runnable::enable_cancel() {
    pthread_setcancelstate(state, &state);
} /// set_cancelable : END

void Runnable::cancellation_point() {
    pthread_testcancel();
} /// detach : END

void Runnable::exit(void* result) {
    pthread_exit(result);
} /// exit : END

Runnable::~Runnable() = default;
