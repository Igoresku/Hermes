//
// Created by Igor Duric on 11/29/19.
//

#include "../include/Result_Queue.h"

Result_Queue::Result_Queue() {
    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&ready, nullptr);
} /// Result_Container : END

void Result_Queue::Deliver(void* result) {
    RAII scoped_key(&mutex);

    auto new_result = new Result_List_Element(result);
    if (head == nullptr)
        head = new_result;
    else
        tail->next = new_result;
    tail = new_result;

    pthread_cond_broadcast(&ready);
} /// Deliver : END

void* Result_Queue::Collect() {
    RAII scoped_key(&mutex);

    while (head == nullptr)
        pthread_cond_wait(&ready, &mutex);

    auto result = head->payload;
    auto temp = head;
    head = head->next;
    if (head == nullptr)
        tail = nullptr;
    delete temp;

    return result;
} /// Collect : END

Result_Queue::~Result_Queue() {
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&ready);
} /// ~Result_Container : END