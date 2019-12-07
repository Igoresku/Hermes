//
// Created by Igor Duric on 12/3/19.
//

#ifndef PATH_FINDING_RESULT_H
#define PATH_FINDING_RESULT_H

#include "Job_Queue.h"
#include "Result_Queue.h"

class Product {
public:
    Product();

    virtual void Deliver() = 0;

    virtual ~Product() = 0;
};


#endif //PATH_FINDING_RESULT_H
