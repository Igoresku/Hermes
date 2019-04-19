//
// Created by Igor Duric on 4/17/19.
//

#include "../include/Zone.h"

const int Zone::SIZE = 8;

void Zone::Find_Path(Cell **starting_positions, int first_array_size, Cell **destination_positions, int second_array_size) {

}

void Zone::Set_Container(Cell* cell) {
    if (number_of_contained % 8 == 0) {
        auto replace_array = new Cell*[number_of_contained + 8];
        for (int i = 0; i < number_of_contained + 8; i++) {
            replace_array[i] = (i < number_of_contained) ? contained[i] : nullptr;
            contained[i] = nullptr;
        }
        delete[] contained;
        contained = replace_array;
    }

    contained[number_of_contained++] = cell;
    Cell::Set_Container(cell);
}