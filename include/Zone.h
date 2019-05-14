//
// Created by Igor Duric on 4/17/19.
//

#ifndef PATH_FINDING_ZONE_H
#define PATH_FINDING_ZONE_H

#include "Cell.h"

class Zone : public Cell {
public:
    Zone(int x, int y, int level, int capacity = 0) : Cell(x, y, level, capacity) {};

    Cell* Adjacent_East(int, int) const override;
    Cell* Adjacent_South(int, int) const override;
    void Add_Neighbour(Cell*) override;
    void Add_Connection(Cell*, Cell*) override;
    void Add_Contained(Cell*) override;
    bool Find_Path(Cell**, int, Cell**, int) override;

    ~Zone() override;
protected:
    // Cell** neighbours = nullptr;
    // int number_of_neighbours = 0;
    Cell*** connections = nullptr;
    int* number_of_connections = nullptr;
    Cell** contained = nullptr;
    int number_of_contained = 0;
};

#endif //PATH_FINDING_ZONE_H
