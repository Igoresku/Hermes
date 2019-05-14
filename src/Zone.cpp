//
// Created by Igor Duric on 4/17/19.
//

#include "../include/Zone.h"

Cell* Zone::Adjacent_East(int i, int j) const {
    for (int m = 0; m < number_of_contained; m++)
        if ((contained[m]->Get_X() == i - 1) && (contained[m]->Get_Y() == j))
            return contained[m];

    return nullptr;
}

Cell* Zone::Adjacent_South(int i, int j) const {
    for (int m = 0; m < number_of_contained; m++)
        if ((contained[m]->Get_X() == i) && (contained[m]->Get_Y() == j - 1))
            return contained[m];

    return nullptr;
}

void Zone::Add_Neighbour(Cell* cell) {
    for (int i = 0; i < number_of_neighbours; i++)
        if (neighbours[i] == cell)
            return;

    int replace_number_of_neighbours = number_of_neighbours + 1;
    auto replace_array_neighbours = new Cell*[replace_number_of_neighbours];
    auto replace_array_connections = new Cell**[replace_number_of_neighbours];
    auto replace_array_number_of_connections = new int[replace_number_of_neighbours];
    for (int i = 0; i < number_of_neighbours; i++) {
        replace_array_neighbours[i] = neighbours[i];
        replace_array_connections[i] = connections[i];
        replace_array_number_of_connections[i] = number_of_connections[i];
        neighbours[i] = nullptr;
        connections[i] = nullptr;
    }

    number_of_neighbours = replace_number_of_neighbours;
    replace_array_neighbours[number_of_neighbours] = cell;
    replace_array_connections[number_of_neighbours] = nullptr;
    replace_array_number_of_connections[number_of_neighbours] = 0;
    delete[] neighbours;
    delete[] connections;
    delete[] number_of_connections;
    neighbours = replace_array_neighbours;
    connections = replace_array_connections;
    number_of_connections = replace_array_number_of_connections;
}

void Zone::Add_Connection(Cell* neighbour, Cell* connection) {
    int i = 0;
    for (; i < number_of_neighbours; i++)
        if (neighbours[i] == neighbour)
            break;

    if (i == number_of_neighbours)
        return;

    auto replace_array_single_connections = new Cell*[number_of_connections[i] + 1];
    for (int j = 0; j < number_of_connections[i]; j++) {
        replace_array_single_connections[j] = connections[i][j];
        connections[i][j] = nullptr;
    }

    replace_array_single_connections[number_of_connections[i]++] = connection;
    delete[] connections[i];
    connections[i] = replace_array_single_connections;
}

void Zone::Add_Contained(Cell* cell) {
    if (number_of_contained % 10 == 0) {
        auto replace_array = new Cell*[number_of_contained + 10];
        for (int i = 0; i < number_of_contained + 10; i++) {
            replace_array[i] = (i < number_of_contained) ? contained[i] : nullptr;
            contained[i] = nullptr;
        }
        delete[] contained;
        contained = replace_array;
    }

    contained[number_of_contained++] = cell;
    cell->Set_Container(this);
}

bool Zone::Find_Path(Cell** starting_positions, int first_array_size, Cell** destination_positions, int second_array_size) {

}

Zone::~Zone() {
    delete[] contained;

    for (int i = 0; i < number_of_neighbours; i++) {
        for (int j = 0; i < number_of_connections[i]; j++)
            connections[i][j] = nullptr;

        delete[] connections[i];
    }
    delete[] connections;
    delete[] number_of_connections;
}