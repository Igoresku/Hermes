//
// Created by Igor Duric on 4/20/19.
//

#include "../include/Map_Abstraction.h"

bool Map_Abstraction::Find_Path(Cell** starting_positions, int first_array_size, Cell** destination_positions, int second_array_size) {

}

Map_Abstraction::~Map_Abstraction() {
    delete[] contained;
}