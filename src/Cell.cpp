//
// Created by Igor Duric on 4/17/19.
//

#include "../include/Cell.h"

void Cell::Make_Neighbours(Cell* first, Cell* second) {
    first->Add_Neighbour(second);
    second->Add_Neighbour(first);
}

void Cell::Make_Neighbours(Cell* first, Cell* second, Cell* connection_1_to_2, Cell* connection_2_to_1) {
    Make_Neighbours(first, second);
    first->Add_Connection(second, connection_1_to_2);
    second->Add_Connection(first, connection_2_to_1);
}

void Cell::Add_Neighbour(Cell* cell) {
    auto replace_array = new Cell*[number_of_neighbours + 1];
    for (int i = 0; i < number_of_neighbours; i++) {
        replace_array[i] = neighbours[i];
        neighbours[i] = nullptr;
    }

    replace_array[number_of_neighbours++] = cell;
    delete[] neighbours;
    neighbours = replace_array;
}

Cell::~Cell() {
    for (int i = 0; i < number_of_neighbours; i++)
        neighbours[i] = nullptr;

    delete[] neighbours;
    container = nullptr;
}