//
// Created by Igor Duric on 4/17/19.
//

#ifndef PATH_FINDING_ZONE_H
#define PATH_FINDING_ZONE_H

#include "Cell.h"

class Zone : public Cell {
private: // meta
    // the maximum number of cells which will be categorized under a zone is size^2
    static const int size;

public:
    Zone(int x, int y, int level_of_abstraction) : Cell(x, y), level_of_abstraction(level_of_abstraction) {};

    void Find_Path(Cell** starting_positions, int first_array_size, Cell** destination_positions, int second_array_size) override;

    // ~Zone() override;
private:
    int level_of_abstraction;

    Cell** contained = nullptr;
    Cell*** connections = nullptr;
    int* number_of_connections = nullptr;
    int number_of_contained = 0;
};


#endif //PATH_FINDING_ZONE_H
