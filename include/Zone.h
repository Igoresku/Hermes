//
// Created by Igor Duric on 4/17/19.
//

#ifndef PATH_FINDING_ZONE_H
#define PATH_FINDING_ZONE_H

#include "Cell.h"

class Zone : public Cell {
public:
    Zone(int x, int y, int capacity = 0) : Cell(x, y, capacity) {};

    bool Find_Path(Cell**, int, Cell**, int) override;

    Cell* Adjacent_East(int, int) const override;
    Cell* Adjacent_South(int, int) const override;
    void Add_Neighbour(Cell*) override;
    void Add_Connection(Cell*, Cell*) override;
    void Add_Contained(Cell*) override;
    // ~Zone() override;
private:
    Cell** contained = nullptr;
    Cell*** connections = nullptr;
    int* number_of_connections = nullptr;
    int number_of_contained = 0;
};

#endif //PATH_FINDING_ZONE_H
