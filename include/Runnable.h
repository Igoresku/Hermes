//
// Created by Igor Duric on 4/17/19.
//

#ifndef PATH_FINDING_RUNNABLE_H
#define PATH_FINDING_RUNNABLE_H

#include <pthread.h>
#include <semaphore.h>

class Runnable {
private:
    static void* Stub(void*);
public:
    Runnable() = default;

    void start();
    bool is_Done() { return done; }

    pthread_t Get_Handler() { return handler; }

    virtual ~Runnable() = 0;

protected:
    virtual void* run() = 0;

    pthread_t handler;

private:
    bool done = false;

    void set_Done() { done = true; }
};

pthread_t Static_Magic(Runnable*);

#endif //PATH_FINDING_RUNNABLE_H
