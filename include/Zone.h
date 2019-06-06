//
// Created by Igor Duric on 4/17/19.
//

#ifndef PATH_FINDING_ZONE_H
#define PATH_FINDING_ZONE_H

#include "Cell.h"

class Zone : public Cell {
private: // meta
    class Zone_List_Element {
    public:
        explicit Zone_List_Element(Cell* payload, Zone_List_Element* next = nullptr): payload(payload), next(next) {};
        Cell* payload;
        Zone_List_Element* next;
};
public:
    Zone(int x, int y, int level, int capacity = 0) : Cell(x, y, level, capacity) {};

    Cell* Adjacent_East(int, int) const override;
    Cell* Adjacent_South(int, int) const override;
    void Add_Neighbour(Cell*) override;
    void Add_Connection(Cell*, Cell*) override;
    void Add_Contained(Cell*) override;
    bool Check_Fragmentation(Cell***&, int*&, int&) final;
    bool Find_Path(Cell**, int, Cell**, int) override;

    ~Zone() override;
protected:
    // Cell** neighbours = nullptr;
    // int number_of_neighbours = 0;
    Cell*** connections = nullptr;
    int* number_of_connections = nullptr;
    Cell** contained = nullptr;
    int number_of_contained = 0;
private:
    static const int CHUNK;
};

#endif //PATH_FINDING_ZONE_H
