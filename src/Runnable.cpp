//
// Created by Igor Duric on 4/17/19.
//

#include "../include/Runnable.h"

void* Runnable::Stub(void* thiz) {
    auto runnable = (Runnable*) thiz;
    void* res = runnable->run();
    runnable->Perform_Waiting_PwD();
    runnable->set_Done();
    return res;
} /// Stub : END

void Runnable::start() {
    pthread_create(&handler, nullptr, Runnable::Stub, (void*) this);
} /// start : END

void Runnable::Add_PwD(Perform_When_Done *pwd) {
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

Runnable::~Runnable() = default;
