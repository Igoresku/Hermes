//
// Created by Igor Duric on 4/17/19.
//

#ifndef PATH_FINDING_RUNNABLE_H
#define PATH_FINDING_RUNNABLE_H

#include <pthread.h>
#include "RAII.h"
#include "Cleanup_Handler.h"

/** Java-style Runnable implemented with PThreads */
class Runnable {
private: /// META
    static void* Stub(void*);

public:
    Runnable();

    void start();
    inline void join(void* = nullptr);
    inline void detach();
    inline void cancel();

    // void push_cleanup_handler(Cleanup_Handler*);
    // void pop_cleanup_handler(int = 0);

    bool is_Done() const { return done; }

    virtual ~Runnable();
protected:
    virtual void* run() = 0;

    inline void disable_cancel();
    inline void enable_cancel();
    inline void cancellation_point();
    void exit(void* = nullptr);

private:
    bool done = false;
    void set_Done() { done = true; }

    pthread_t handler;
    int state;
};

#endif //PATH_FINDING_RUNNABLE_H
