//
// Created by Igor Duric on 4/17/19.
//

#ifndef PATH_FINDING_CELL_ABSTRACTION_H
#define PATH_FINDING_CELL_ABSTRACTION_H


class Cell {
public: // meta
    /** Makes the basic cells neighbours to each other */
    static void Make_Neighbours(Cell* first, Cell* second);
    /** Makes cells that are actually zones neighbours to each other, and connects them accordingly */
    static void Make_Neighbours(Cell* first, Cell* second, Cell* connection_1_to_2, Cell* connection_2_to_1);
public:
    Cell(int x, int y, int level, int capacity = 0) : x(x), y(y), level(level), capacity(capacity) {};
    Cell(const Cell& cell) : x(cell.Get_X()),  y(cell.Get_Y()), level(cell.Get_Level()), capacity(cell.Get_Capacity()) {};
    Cell(Cell&&) = delete;

    /** Trivial functions **/
    int Get_X() const { return x; };
    int Get_Y() const { return y; };
    int Get_Level() const { return level; };
    int Get_Capacity() const { return capacity; };
    Cell* Get_Container() const { return container; };
    Cell** const Get_Neighbours() const { return neighbours; };
    int Get_Number_Of_Neighbours() const { return number_of_neighbours; };
    void Update_Capacity(int new_capacity) { if (new_capacity > capacity) capacity = new_capacity; };
    void Set_Container(Cell* cell) { if (container == nullptr) container = cell; };

    /** Trivial virtual functions or those that exist simply to be implemented in Zone but callable in Cell **/
    virtual Cell* Adjacent_Vertical(int i, int j) const { return nullptr; };
    virtual Cell* Adjacent_Horizontal(int i, int j) const { return nullptr; };
    virtual void Add_Connection(Cell*, Cell*) {};
    virtual void Add_Contained(Cell*) {};
    virtual void Add_Neighbour(Cell*);

    /** Check if all contained cells inside a zone are connected to each other:
     * subzones - collections of connected cells inside the zone
     * number_of_subzones_elements - number of cells in each of the subzones
     * number_of_subzones - number of identified subzones
     * RETURN - is the zone in question actually divided into sub-zones? */
    virtual bool Fragment(Cell***& subzones, int*& number_of_subzones_elements, int& number_of_subzones) { return false; };
    /** Replaces the designated zone with the collection of given subzones:
     * zone - the zone that is to be replaced
     * subzones - collections of connected cells inside the zone
     * number_of_subzones_elements - number of cells in each of the subzones
     * number_of_subzones - number of identified subzones
     * */
    virtual void Replace(Cell* zone, Cell*** subzones, int* number_of_subzones_elements, int number_of_subzones) {};
    /*** */
    virtual bool Find_Path(Cell** starting_positions, int number_1, Cell** ending_positions, int number_2) { return true; };

    virtual ~Cell();
protected:
    /** All neighbours to this cell and the number of them */
    Cell** neighbours = nullptr;
    int number_of_neighbours = 0;
private:
    /** Trivial information about the cell */
    const int x;
    const int y;
    const int level;
    int capacity;
    Cell* container = nullptr;
};

#endif //PATH_FINDING_CELL_ABSTRACTION_H
