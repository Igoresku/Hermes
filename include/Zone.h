//
// Created by Igor Duric on 4/17/19.
//

#ifndef PATH_FINDING_ZONE_H
#define PATH_FINDING_ZONE_H

#include "Cell.h"

#define ZONE_ALLOCATION_CHUNK 10

/** Cell that contains other cells, represents a single point of abstracted map */
class Zone : public Cell {
private: /// META
    class Zone_List_Element {
    public:
        explicit Zone_List_Element(Cell* payload, Zone_List_Element* next = nullptr): payload(payload), next(next) {};
        Cell* payload;
        Zone_List_Element* next;
    };
public:
    Zone(int x, int y, int level, int capacity = 0, bool fragmented = false) : Cell(x, y, level, capacity), fragmented(fragmented) {};

    Cell* Adjacent_Vertical(int i, int j) const override;
    Cell* Adjacent_Horizontal(int i, int j) const override;
    Cell** const Get_Connections(Cell* neighbour) const override;
    int Get_Number_Of_Connections(Cell* neighbour) const override;
    void Add_Connection(Cell* neighbour, Cell* connection) override;
    void Remove_Connection(Cell* neighbour, Cell* connection) override;
    void Add_Contained(Cell* cell) override;
    void Remove_Contained(Cell* cell) override;
    void Add_Neighbour(Cell* cell) override;
    void Remove_Neighbour(Cell* cell) override;

    bool Fragment(Cell***& subzones, int*& number_of_subzones_elements, int& number_of_subzones) final;
    /** All functions that remove cells from a structure of a zone MUST BE USED CAREFULLY,
     * since the structures are extremely interconnected and dependant on each other */
    void Replace(Cell* zone, Cell*** subzones, int* number_of_subzones_elements, int number_of_subzones) final;
    void Wipe_Clean() override;
    bool Find_Path(Cell**, int, Cell**, int) override;

    ~Zone() override;
protected:
    // TODO: Make connections actual separate objects that contain two lower level cells between connected zones
    /** Contained cells that are connections to neighbours and the number of connections to each of them;
     * each entry in connections array is list of cells that are adjacent to neighbour of the same index
     * with number of them being in the same index of number_of_connections array, all cells that connect
     * to neighbours are also contained cells */
    Cell*** connections = nullptr;
    int* number_of_connections = nullptr;

    Cell** contained = nullptr;
    int number_of_contained = 0;
private:
    /// Was this zone created normally or through fragmentation?
    bool fragmented;
};

#endif //PATH_FINDING_ZONE_H
