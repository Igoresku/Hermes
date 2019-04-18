//
// Created by Igor Duric on 4/17/19.
//

#ifndef PATH_FINDING_ZONE_H
#define PATH_FINDING_ZONE_H

#include "Cell.h"

class Zone : public Cell {
private: // meta
    static int size;

public: // meta
    static void Set_Size(int size) { Zone::size = size; };

public:
    explicit Zone(const Cell&);

    // ~Zone() override;
private:
    Cell** contained;
    Cell*** connections;
};


#endif //PATH_FINDING_ZONE_H
