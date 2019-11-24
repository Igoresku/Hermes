//
// Created by Igor Duric on 11/23/19.
//

#ifndef PATH_FINDING_SIGNAL_FINISHED_H
#define PATH_FINDING_SIGNAL_FINISHED_H

#include <stack>
#include <semaphore.h>
#include "Perform_When_Done.h"

class Raise_Finished : public Perform_When_Done {
public:
    explicit Raise_Finished(sem_t, std::stack<int>*, sem_t, int);

    void Perform_Action() override;

    ~Raise_Finished() override;
private:
    sem_t signal;
    std::stack<int>* master;
    int index;
    sem_t master_mutex;
};


#endif //PATH_FINDING_SIGNAL_FINISHED_H
