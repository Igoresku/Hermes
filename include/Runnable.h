//
// Created by Igor Duric on 4/17/19.
//

#ifndef PATH_FINDING_RUNNABLE_H
#define PATH_FINDING_RUNNABLE_H

#include <pthread.h>
#include "Perform_When_Done.h"

class Runnable {
private: // Meta
    static void* Stub(void*);

    class PwD_List {
    public:
        explicit PwD_List(Perform_When_Done* payload, PwD_List* next = nullptr) : payload(payload), next(next) {};
        Perform_When_Done* payload;
        PwD_List* next;
    };
public:
    Runnable() = default;

    void start();

    bool is_Done() const { return done; }
    pthread_t Get_Handler() const { return handler; }
    void Add_PwD(Perform_When_Done*);

    virtual ~Runnable() = 0;
protected:
    virtual void* run() = 0;

    pthread_t handler;
private:
    bool done = false;
    void set_Done() { done = true; }

    void Perform_Waiting_PwD();
    PwD_List* head = nullptr;
    PwD_List* tail = nullptr;
};

#endif //PATH_FINDING_RUNNABLE_H
