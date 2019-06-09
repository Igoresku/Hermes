//
// Created by Igor Duric on 4/17/19.
//

#include "../include/Zone.h"

const int Zone::CHUNK = 10;

Cell* Zone::Adjacent_Vertical(int i, int j) const {
    for (int m = 0; m < number_of_contained; m++)
        if ((contained[m]->Get_X() == i - 1) && (contained[m]->Get_Y() == j))
            return contained[m];

    return nullptr;
}

Cell* Zone::Adjacent_Horizontal(int i, int j) const {
    for (int m = 0; m < number_of_contained; m++)
        if ((contained[m]->Get_X() == i) && (contained[m]->Get_Y() == j - 1))
            return contained[m];

    return nullptr;
}

void Zone::Add_Connection(Cell* neighbour, Cell* connection) {
    int i = 0;
    for (; i < number_of_neighbours; i++)
        if (neighbours[i] == neighbour)
            break;

    if (i == number_of_neighbours)
        return;

    auto replace_single_connections = new Cell*[number_of_connections[i] + 1];
    for (int j = 0; j < number_of_connections[i]; j++) {
        replace_single_connections[j] = connections[i][j];
        connections[i][j] = nullptr;
    }

    replace_single_connections[number_of_connections[i]++] = connection;
    delete[] connections[i];
    connections[i] = replace_single_connections;
}

void Zone::Remove_Connection(Cell* neighbour, Cell* connection) {
    int i = 0;
    for (; i < number_of_neighbours; i++)
        if (neighbours[i] == neighbour)
            break;

    if (i == number_of_neighbours)
        return;

    int j = 0;
    for (; j < number_of_connections[i]; j++)
        if (connections[i][j] == connection)
            break;

    if (j == number_of_connections[i])
        return;

    if (number_of_connections[i] == 1) {
        // if this is the last connection to the neighbour, then remove the neighbour completely
        Remove_Neighbour(neighbour);
    } else {
        auto replace_single_connections = new Cell*[number_of_connections[i] - 1];
        for (int k = 0; k < j; j++) {
            replace_single_connections[k] = connections[i][k];
            connections[i][k] = nullptr;
        }
        for (int k = j; k < number_of_connections[i] - 1; k++) {
            replace_single_connections[k] = connections[i][k + 1];
            connections[i][k + 1] = nullptr;
        }
        connections[number_of_connections[i] - 1] = nullptr;

        number_of_connections[i] -= 1;
        delete[] connections[i];
        connections[i] = replace_single_connections;
    }
}

void Zone::Add_Contained(Cell* cell) {
    if (number_of_contained % CHUNK == 0) {
        auto replace_array = new Cell*[number_of_contained + CHUNK];
        for (int i = 0; i < number_of_contained + CHUNK; i++) {
            replace_array[i] = (i < number_of_contained) ? contained[i] : nullptr;
            contained[i] = nullptr;
        }
        delete[] contained;
        contained = replace_array;
    }

    contained[number_of_contained++] = cell;
    cell->Set_Container(this);
}

void Zone::Remove_Contained(Cell* cell) {
    int i = 0;
    for (; i < number_of_contained; i++)
        if (contained[i] == cell)
            break;

    if (i == number_of_contained)
        return;

    for (int j = i; j < number_of_contained - 1; j++)
        contained[j] = contained[j + 1];
    contained[number_of_contained - 1] = nullptr;
    number_of_contained -= 1;

    if (number_of_contained % CHUNK == 0) {
        auto replace_contained = new Cell*[number_of_contained];
        for (int j = 0; j < number_of_contained; j++) {
            replace_contained[j] = contained[j];
            contained[j] = nullptr;
        }
        delete[] contained;
        contained = replace_contained;
    }

    int j = 0, k = 0;
    for (; j < number_of_neighbours; j++)
        for (; k < number_of_connections[j]; k++)
            if (connections[j][k] == cell) {
                Remove_Connection(neighbours[j], connections[j][k]);
                break;
            }
}

void Zone::Add_Neighbour(Cell* cell) {
    for (int i = 0; i < number_of_neighbours; i++)
        if (neighbours[i] == cell)
            return;

    int replace_number_of_neighbours = number_of_neighbours + 1;
    auto replace_neighbours = new Cell*[replace_number_of_neighbours];
    auto replace_connections = new Cell**[replace_number_of_neighbours];
    auto replace_number_of_connections = new int[replace_number_of_neighbours];
    for (int i = 0; i < number_of_neighbours; i++) {
        replace_neighbours[i] = neighbours[i];
        replace_connections[i] = connections[i];
        replace_number_of_connections[i] = number_of_connections[i];
        neighbours[i] = nullptr;
        connections[i] = nullptr;
    }

    number_of_neighbours = replace_number_of_neighbours;
    replace_neighbours[number_of_neighbours] = cell;
    replace_connections[number_of_neighbours] = nullptr;
    replace_number_of_connections[number_of_neighbours] = 0;
    delete[] neighbours;
    delete[] connections;
    delete[] number_of_connections;
    neighbours = replace_neighbours;
    connections = replace_connections;
    number_of_connections = replace_number_of_connections;
}

void Zone::Remove_Neighbour(Cell *cell) {
    int i = 0;
    for (; i < number_of_neighbours; i++)
        if (neighbours[i] == cell)
            break;

    if (i == number_of_neighbours)
        return;

    int replace_number_of_neighbours = number_of_neighbours - 1;
    auto replace_neighbours = new Cell*[replace_number_of_neighbours];
    auto replace_connections = new Cell**[replace_number_of_neighbours];
    auto replace_number_of_connections = new int[replace_number_of_neighbours];
    for (int j = 0; j < i; j++) {
        replace_neighbours[j] = neighbours[j];
        replace_connections[j] = connections[j];
        replace_number_of_connections[j] = number_of_connections[j];
        neighbours[j] = nullptr;
        connections[j] = nullptr;
    }
    for (int j = i; j < number_of_neighbours - 1; j++) {
        replace_neighbours[j] = neighbours[j + 1];
        replace_connections[j] = connections[j + 1];
        replace_number_of_connections[j] = number_of_connections[j + 1];
        neighbours[j + 1] = nullptr;
        connections[j + 1] = nullptr;
    }
    neighbours[number_of_neighbours - 1] = nullptr;
    connections[number_of_neighbours - 1] = nullptr;

    number_of_neighbours = replace_number_of_neighbours;
    delete[] neighbours;
    delete[] connections;
    delete[] number_of_connections;
    neighbours = replace_neighbours;
    connections = replace_connections;
    number_of_connections = replace_number_of_connections;
}

bool Zone::Fragment(Cell***& subzones, int*& number_of_subzones_elements, int& number_of_subzones) {
    /* First I reset the state of the variables that I fill with data and create a copy of cells
     * contained in the zone that I can safely manipulate without changing the original array */
    for (int i = 0; i < number_of_subzones; i++) {
        for (int j = 0; j < number_of_subzones_elements[i]; j++)
            subzones[i][j] = nullptr;

        delete[] subzones[i];
    }
    number_of_subzones = 0;
    Zone::Zone_List_Element* head_contained_copy = nullptr;
    for (int i = number_of_contained - 1; i >= 0; i--)
        head_contained_copy = new Zone::Zone_List_Element(contained[i], head_contained_copy);

    /* I pick a single contained cell and create a subzone from it and all reachable cells,
     * repeating it as long as there is a cell that has not been visited in any way */
    while (head_contained_copy != nullptr) {
        auto replace_subzones = new Cell**[number_of_subzones + 1];
        auto replace_number_of_subzones_elements = new int[number_of_subzones + 1];
        for (int i = 0; i < number_of_subzones; i++) {
            replace_subzones[i] = subzones[i];
            subzones[i] = nullptr;
            replace_number_of_subzones_elements[i] = number_of_subzones_elements[i];
        }
        delete[] subzones;
        delete[] number_of_subzones_elements;
        subzones = replace_subzones;
        number_of_subzones_elements = replace_number_of_subzones_elements;
        subzones[number_of_subzones] = new Cell*[CHUNK];
        number_of_subzones_elements[number_of_subzones] = 0;
        number_of_subzones += 1;

        subzones[number_of_subzones - 1][0] = head_contained_copy->payload;
        number_of_subzones_elements[number_of_subzones - 1] = 1;
        head_contained_copy->payload = nullptr;
        if (head_contained_copy->next != nullptr) {
            auto aux = head_contained_copy;
            head_contained_copy = head_contained_copy->next;
            aux->next = nullptr;
            delete aux;
        } else {
            delete head_contained_copy;
            head_contained_copy = nullptr;
        }

        /* I add all neighbours of the current cell to the subzone(that have
         * not yet been added and those that are members of the current zone) */
        bool already_placed = false;
        for (int i = 0; i < number_of_subzones_elements[number_of_subzones - 1]; i++) {
            auto neighbours = subzones[number_of_subzones - 1][i]->Get_Neighbours();

            for (int j = 0; j < subzones[number_of_subzones - 1][i]->Get_Number_Of_Neighbours(); j++) {

                for (int k = 0; k < number_of_subzones_elements[number_of_subzones - 1]; k++) {
                    if (neighbours[i] == subzones[number_of_subzones -1][k]) {
                        already_placed = true;
                        break;
                    }
                }

                if (!already_placed) {
                    auto follower = head_contained_copy;

                    for (auto iterator = head_contained_copy; iterator != nullptr; iterator = iterator->next) {
                        if (neighbours[i] == iterator->payload) {

                            if (number_of_subzones_elements[number_of_subzones - 1] % CHUNK == 0) {
                                auto replace_subzone = new Cell*[number_of_subzones_elements[number_of_subzones - 1] + CHUNK];

                                for (int l = 0; l < number_of_subzones_elements[number_of_subzones - 1]; l++) {
                                    replace_subzone[l] = subzones[number_of_subzones - 1][l];
                                    subzones[number_of_subzones - 1][l] = nullptr;
                                }
                                delete[] subzones[number_of_subzones - 1];
                                subzones[number_of_subzones - 1] = replace_subzone;
                            }
                            number_of_subzones_elements[number_of_subzones - 1] += 1;
                            subzones[number_of_subzones - 1][number_of_subzones_elements[number_of_subzones - 1]] = neighbours[i];

                            if (follower == head_contained_copy) {
                                head_contained_copy = head_contained_copy->next;
                                follower->payload = nullptr;
                                follower->next = nullptr;
                                delete follower;
                            } else {
                                follower->next = iterator->next;
                                iterator->payload = nullptr;
                                iterator->next = nullptr;
                                delete iterator;
                            }

                            break;
                        }

                        follower = iterator;
                    }// for : iterator
                } // if : !already_placed

            } // for : j
        } // for : i

    } // while (head_contained_copy != nullptr)

    return (number_of_subzones > 1);
}

void Zone::Replace(Cell* zone, Cell*** subzones, int* number_of_subzones_elements, int number_of_subzones) {
    // this function has the responsibilty of cleaning up everything relating to zone that is being removed 
    Remove_Contained(zone);
    delete zone;
}

void Zone::Wipe_Clean() {
    container = nullptr;
    for (int i = 0; i < number_of_neighbours; i++) {
        neighbours[i] = nullptr;
        for (int j = 0; j < number_of_connections[i]; j++)
            connections[i][j] = nullptr;

        delete[] connections[i];
        connections[i] = nullptr;
    }
    number_of_neighbours = 0;
    delete[] neighbours;
    delete[] connections;
    delete[] number_of_connections;

    for (int i = 0; i < number_of_contained; i++)
        contained[i] = nullptr;

    number_of_contained = 0;
    delete[] contained;
}

bool Zone::Find_Path(Cell** starting_positions, int first_array_size, Cell** destination_positions, int second_array_size) {

}

Zone::~Zone() {
    delete[] contained;

    for (int i = 0; i < number_of_neighbours; i++) {
        // neighbours are not deleted since they are not this cells responsibility
        neighbours[i] = nullptr;
        for (int j = 0; i < number_of_connections[i]; j++)
            connections[i][j] = nullptr;

        delete[] connections[i];
    }
    delete[] connections;
    delete[] number_of_connections;
}