//
// Created by Igor Duric on 4/17/19.
//

#ifndef PATH_FINDING_CELL_ABSTRACTION_H
#define PATH_FINDING_CELL_ABSTRACTION_H


class Cell {
public:
    Cell(int, int);
    Cell(const Cell&);
    Cell(Cell&&) = delete;

    int Get_X() const { return x; };
    int Get_Y() const { return y; };

    void Set_Container(Cell* cell) { if (container == nullptr) container = cell; };
    void Add_Neighbour(Cell*);

    // virtual ~Cell();
private:
    int x;
    int y;
    int number_of_neighbours = 0;

    Cell* container = nullptr;
    Cell** neighbours = nullptr;
};


#endif //PATH_FINDING_CELL_ABSTRACTION_H
