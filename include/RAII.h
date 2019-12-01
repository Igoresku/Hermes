//
// Created by Igor Duric on 11/25/19.
//

#ifndef PATH_FINDING_RAII_H
#define PATH_FINDING_RAII_H

#include <pthread.h>

/// Resource Acquisition Is Initialization
/** Enables RAII type of locks and safety associated with them */
class RAII {
public:
    explicit RAII(pthread_mutex_t*);

    ~RAII();
private:
    pthread_mutex_t* mutex;
};


#endif //PATH_FINDING_RAII_H
