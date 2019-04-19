//
// Created by Igor Duric on 4/17/19.
//

#ifndef PATH_FINDING_ZONE_H
#define PATH_FINDING_ZONE_H

#include "Cell.h"

class Zone : public Cell {
private: // meta
    // the maximum number of cells which will be categorized under a zone is size^2
    static const int SIZE;

public:
    Zone(int x, int y, int capacity = 0) : Cell(x, y, capacity) {};

    void Find_Path(Cell** starting_positions, int first_array_size, Cell** destination_positions, int second_array_size) override;
    void Set_Container(Cell*) override;
    // ~Zone() override;
private:
    Cell** contained = nullptr;
    Cell*** connections = nullptr;
    int* number_of_connections = nullptr;
    int number_of_contained = 0;
};


#endif //PATH_FINDING_ZONE_H
