//
// Created by Igor Duric on 4/17/19.
//

#include "../include/Runnable.h"

void* Runnable::Stub(void* me) {
    auto runnable = (Runnable*) me;
    void* res = runnable->run();
    runnable->Perform_Waiting_PwD();
    runnable->set_Done();
    return res;
} /// Stub : END

Runnable::Runnable() {
    pthread_mutex_init(&pwd_mutex, nullptr);
}

void Runnable::start() {
    pthread_create(&handler, nullptr, Runnable::Stub, (void*) this);
} /// start : END

void Runnable::join(void* result) {
    pthread_join(handler, &result);
} /// join : END

void Runnable::detach() {
    pthread_detach(handler);
} /// detach : END

void Runnable::exit(void* result) {
    pthread_exit(result);
}

void Runnable::Add_PwD(Perform_When_Done* pwd) {
    RAII raii(&pwd_mutex);

    if (done)
        return;

    auto new_waiting = new PwD_List(pwd);
    if (head == nullptr)
        head = new_waiting;
    else
        tail->next = new_waiting;
    tail = new_waiting;
} /// Add_Waiting_Signal : END

void Runnable::Perform_Waiting_PwD() {
    auto iterator = head;
    PwD_List* scout;

    while (iterator != tail) {
        scout = iterator->next;
        iterator->payload->Perform_Action();
        delete iterator->payload;
        delete iterator;
        iterator = scout;
    }
    if (iterator != nullptr) {
        iterator->payload->Perform_Action();
        delete iterator->payload;
        delete iterator;
    }
} /// Signal_Waiting : END

Runnable::~Runnable() {
    pthread_mutex_destroy(&pwd_mutex);
};
