//
// Created by Igor Duric on 4/17/19.
//

#ifndef PATH_FINDING_CELL_ABSTRACTION_H
#define PATH_FINDING_CELL_ABSTRACTION_H


class Cell {
public:
    Cell(int x, int y) : x(x), y(y) {};
    Cell(const Cell& cell) : x(cell.Get_X()),  y(cell.Get_Y()) {};
    Cell(Cell&&) = delete;

    int Get_X() const { return x; };
    int Get_Y() const { return y; };

    void Set_Container(Cell* cell) { if (container == nullptr) container = cell; };
    void Add_Neighbour(Cell*);

    virtual void Find_Path(Cell** starting_positions, int first_array_size, Cell** destination_positions, int second_array_size) {};

    // virtual ~Cell();
private:
    int x;
    int y;
    Cell* container = nullptr;
    Cell** neighbours = nullptr;
    int number_of_neighbours = 0;
};


#endif //PATH_FINDING_CELL_ABSTRACTION_H
