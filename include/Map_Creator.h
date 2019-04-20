//
// Created by Igor Duric on 4/19/19.
//

#ifndef PATH_FINDING_MAP_CREATOR_H
#define PATH_FINDING_MAP_CREATOR_H

#include "Runnable.h"
#include "Invalid_Parameters.h"

class Map_Creator: public Runnable {
public: // Meta
    static Map_Creator* Factory(int = 262144, int = 8, int = 3) noexcept(false);

public:
    Map_Creator(int, int, int);

    void* run() override;

private:
    int dimensions;
    int abstraction_size;
    int max_agent_size;
};

#endif //PATH_FINDING_MAP_CREATOR_H
