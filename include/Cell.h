//
// Created by Igor Duric on 4/17/19.
//

#ifndef PATH_FINDING_CELL_ABSTRACTION_H
#define PATH_FINDING_CELL_ABSTRACTION_H

/** Cell represents a single point of a (real) map, it fulfills a role in
 * "Composite" pattern, where a Zone class can contain a number of Cells */
class Cell {
public: /// META
    static bool Are_Adjacent(Cell* first, Cell* second);
    /// Makes the basic Cells neighbours to each other
    static void Make_Neighbours(Cell* first, Cell* second);
    /// Makes Cells that are actually zones neighbours to each other, and connects them accordingly
    static void Make_Neighbours(Cell* first, Cell* second, Cell* connection_1_to_2, Cell* connection_2_to_1);
public:
    Cell(const Cell& UoS) : x(UoS.Get_X()),  y(UoS.Get_Y()), level(UoS.Get_Level()), capacity(UoS.Get_Capacity()) {};
    Cell(Cell&&) = delete;
    Cell(int x, int y, int level, int capacity = 0) : x(x), y(y), level(level), capacity(capacity) {};

    int Get_X() const { return x; };
    int Get_Y() const { return y; };
    int Get_Level() const { return level; };
    int Get_Capacity() const { return capacity; };
    Cell* Get_Container() const { return container; };
    Cell** const Get_Neighbours() const { return neighbours; };
    int Get_Number_Of_Neighbours() const { return number_of_neighbours; };
    void Update_Capacity(int new_capacity) { if (new_capacity > capacity) capacity = new_capacity; };
    void Set_Container(Cell* Cell) { container = Cell; };

    virtual Cell* Adjacent_Vertical(int i, int j) const { return nullptr; };
    virtual Cell* Adjacent_Horizontal(int i, int j) const { return nullptr; };
    virtual Cell** const Get_Connections(Cell* neighbour) const { return nullptr; };
    virtual int Get_Number_Of_Connections(Cell* neighbour) const { return 0; };
    virtual void Add_Connection(Cell* neighbour, Cell* connection) {};
    virtual void Remove_Connection(Cell* neighbour, Cell* connection) {};
    virtual void Add_Contained(Cell* Cell) {};
    virtual void Remove_Contained(Cell* Cell) {};
    virtual void Add_Neighbour(Cell* Cell);
    virtual void Remove_Neighbour(Cell* Cell);
    
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
     * number_of_subzones - number of identified subzones */
    virtual void Replace(Cell* zone, Cell*** subzones, int* number_of_subzones_elements, int number_of_subzones) {};
    /** This function is called when the cell is being fragmented and replaced for safe pointer deletion,
     * it is similar to destructor but not the same, where destructor takes with itself all the data inside
     * the arrays, Wipe_Clean prevents this */
    virtual void Wipe_Clean();
    /*** */
    virtual bool Find_Path(Cell** starting_positions, int size_1, Cell** destination_positions, int size_2) { return true; };

    virtual ~Cell();
protected:
    Cell** neighbours = nullptr;
    int number_of_neighbours = 0;
    Cell* container = nullptr;
private:
    const int x;
    const int y;
    const int level;
    int capacity;
};

#endif //PATH_FINDING_CELL_ABSTRACTION_H
