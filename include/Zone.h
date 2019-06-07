//
// Created by Igor Duric on 4/17/19.
//

#ifndef PATH_FINDING_ZONE_H
#define PATH_FINDING_ZONE_H

#include "Cell.h"

class Zone : public Cell {
private: // meta
    /** Nested trivial list element used inside Fragment function */
    class Zone_List_Element {
    public:
        explicit Zone_List_Element(Cell* payload, Zone_List_Element* next = nullptr): payload(payload), next(next) {};
        Cell* payload;
        Zone_List_Element* next;
};
public:
    Zone(int x, int y, int level, int capacity = 0) : Cell(x, y, level, capacity) {};

    Cell* Adjacent_Vertical(int, int) const override;
    Cell* Adjacent_Horizontal(int, int) const override;
    void Add_Neighbour(Cell*) override;
    void Add_Connection(Cell*, Cell*) override;
    void Add_Contained(Cell*) override;
    bool Fragment(Cell***&, int*&, int&) final;
    void Replace(Cell*, Cell***, int*, int) final;
    bool Find_Path(Cell**, int, Cell**, int) override;

    ~Zone() override;
protected:
    // TODO: Make connections actual separate objects that contain two lower level cells between connected zones
    /** Contained cells that are connections to  */
    Cell*** connections = nullptr;
    int* number_of_connections = nullptr;
    /** */
    Cell** contained = nullptr;
    int number_of_contained = 0;
private:
    /** Allocation chunk, made simply for better control of the code, default value is 10 for no particular reason */
    static const int CHUNK;
};

#endif //PATH_FINDING_ZONE_H
