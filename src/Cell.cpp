//
// Created by Igor Duric on 4/17/19.
//

#include "../include/Cell.h"

bool Cell::Are_Adjacent(Cell* first, Cell* second) {
    bool adjacent_x = ((first->Get_X() - second->Get_X()) == 1) || ((first->Get_X() - second->Get_X()) == -1);
    bool adjacent_y = ((first->Get_Y() - second->Get_Y()) == 1) || ((first->Get_Y() - second->Get_Y()) == -1);
    return adjacent_x && adjacent_y;
} /// Are_Adjacent : END

void Cell::Make_Neighbours(Cell* first, Cell* second) {
    first->Add_Neighbour(second);
    second->Add_Neighbour(first);
} /// Make_Neighbours : END

void Cell::Make_Neighbours(Cell* first, Cell* second, Cell* connection_1_to_2, Cell* connection_2_to_1) {
    Make_Neighbours(first, second);
    first->Add_Connection(second, connection_1_to_2);
    second->Add_Connection(first, connection_2_to_1);
} /// Make_Neighbours : END

void Cell::Add_Neighbour(Cell* cell) {
    for (int i = 0; i < number_of_neighbours; i++)
        if (neighbours[i] == cell)
            return;

    auto replace_array = new Cell*[number_of_neighbours + 1];
    for (int i = 0; i < number_of_neighbours; i++) {
        replace_array[i] = neighbours[i];
        neighbours[i] = nullptr;
    }

    replace_array[number_of_neighbours++] = cell;
    delete[] neighbours;
    neighbours = replace_array;
} /// Add_Neighbour : END

void Cell::Remove_Neighbour(Cell* cell) {
    int i = 0;
    for (; i < number_of_neighbours; i++)
        if (neighbours[i] == cell)
            break;

    if (i == number_of_neighbours)
        return;

    auto replace_neighbours = new Cell*[number_of_neighbours - 1];
    for (int j = 0; j < i; j++) {
        replace_neighbours[j] = neighbours[j];
        neighbours[j] = nullptr;
    }
    for (int j = i; j < number_of_neighbours - 1; j++) {
        replace_neighbours[j] = neighbours[j + 1];
        neighbours[j + 1] = nullptr;
    }
    neighbours[number_of_neighbours - 1] = nullptr;

    number_of_neighbours -= 1;
    delete[] neighbours;
    neighbours = replace_neighbours;
} /// Remove_Neighbour : END

void Cell::Wipe_Clean() {
    container = nullptr;
    for (int i = 0; i < number_of_neighbours; i++)
        neighbours[i] = nullptr;

    number_of_neighbours = 0;
    delete[] neighbours;
} /// Wipe_Clean : END

Cell::~Cell() {
    delete[] neighbours;
}
