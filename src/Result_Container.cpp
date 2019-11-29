//
// Created by Igor Duric on 11/29/19.
//

#include "../include/Result_Container.h"

Result_Container::Result_Container() {
    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&ready, nullptr);
} /// Result_Container : END

void Result_Container::Deliver(void* result) {
    RAII scoped_key(&mutex);

    Deliver_Result(result);
    Acknowledge_Delivery();
    pthread_cond_broadcast(&ready);
} /// Deliver : END

void* Result_Container::Collect() {
    RAII scoped_key(&mutex);

    while (!Collectible())
        pthread_cond_wait(&ready, &mutex);

    Acknowledge_Collection();
    return Collect_Result();
} /// Collect : END

void Result_Container::Acknowledge_Delivery() {
    result_ready = true;
} /// Acknowledge_Delivery : END

void Result_Container::Acknowledge_Collection() {
    result_ready = false;
} /// Acknowledge_Collection : END

bool Result_Container::Collectible() {
    return result_ready;
} /// Acknowledge_Collection : END

void Result_Container::Deliver_Result(void* result) {
    this->result = result;
} /// Deliver_Result : END

void* Result_Container::Collect_Result() {
    return result;
} /// Deliver_Result : END

Result_Container::~Result_Container() {
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&ready);
} /// ~Result_Container : END