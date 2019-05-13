//
// Created by Igor Duric on 4/17/19.
//

#ifndef PATH_FINDING_CELL_ABSTRACTION_H
#define PATH_FINDING_CELL_ABSTRACTION_H


class Cell {
public:
    Cell(int x, int y, int level, int capacity = 0) : x(x), y(y), level(level), capacity(capacity) {};
    Cell(const Cell& cell) : x(cell.Get_X()),  y(cell.Get_Y()), level(cell.Get_Level()), capacity(cell.Get_Capacity()) {};
    Cell(Cell&&) = delete;

    /** Trivial functions **/
    int Get_X() const { return x; };
    int Get_Y() const { return y; };
    int Get_Level() const { return level; };
    int Get_Capacity() const { return capacity; };
    void Update_Capacity(int new_capacity) { if (new_capacity > capacity) capacity = new_capacity; };
    void Set_Container(Cell* cell) { container = cell; };

    virtual Cell* Adjacent_East(int i, int j) const { return nullptr; };
    virtual Cell* Adjacent_South(int i, int j) const { return nullptr; };
    virtual void Add_Neighbour(Cell*);
    virtual void Add_Connection(Cell*, Cell*) {};
    virtual void Add_Contained(Cell*) {};
    virtual bool Find_Path(Cell**, int, Cell**, int) { return true; };

    virtual ~Cell();
protected:
    Cell** neighbours = nullptr;
    int number_of_neighbours = 0;

private:
    const int x;
    const int y;
    const int level;
    int capacity;
    Cell* container = nullptr;
};

#endif //PATH_FINDING_CELL_ABSTRACTION_H
