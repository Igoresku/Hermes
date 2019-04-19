//
// Created by Igor Duric on 4/17/19.
//

#ifndef PATH_FINDING_CELL_ABSTRACTION_H
#define PATH_FINDING_CELL_ABSTRACTION_H


class Cell {
public:
    Cell(int x, int y, int capacity = 0) : x(x), y(y), capacity(capacity) {};
    Cell(const Cell& cell) : x(cell.Get_X()),  y(cell.Get_Y()), capacity(cell.Get_Capacity()) {};
    Cell(Cell&&) = delete;

    int Get_X() const { return x; };
    int Get_Y() const { return y; };
    int Get_Capacity() const { return capacity; };

    void Update_Capacity(int new_capacity) { if (new_capacity > capacity) capacity = new_capacity; };

    virtual void Set_Container(Cell* cell) { container = cell; };
    void Add_Neighbour(Cell*);

    virtual void Find_Path(Cell** starting_positions, int first_array_size, Cell** destination_positions, int second_array_size) {};

    // virtual ~Cell();
private:
    const int x;
    const int y;
    int capacity;
    Cell* container = nullptr;
    Cell** neighbours = nullptr;
    int number_of_neighbours = 0;
};

#endif //PATH_FINDING_CELL_ABSTRACTION_H
