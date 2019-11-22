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
} /// Adjacent_Vertical : END

Cell* Zone::Adjacent_Horizontal(int i, int j) const {
    for (int m = 0; m < number_of_contained; m++)
        if ((contained[m]->Get_X() == i) && (contained[m]->Get_Y() == j - 1))
            return contained[m];

    return nullptr;
} /// Adjacent_Horizontal : END

Cell** const Zone::Get_Connections(Cell* neighbour) const {
    int i = 0;
    for (; i < number_of_neighbours; i++)
        if (neighbours[i] == neighbour)
            return connections[i];

    return nullptr;
} /// Get_Connections : END

int Zone::Get_Number_Of_Connections(Cell* neighbour) const {
    int i = 0;
    for (; i < number_of_neighbours; i++)
        if (neighbours[i] == neighbour)
            return number_of_connections[i];

    return -1;
} /// Get_Number_Of_Connections : END

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
} /// Add_Connection : END

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
} /// Remove_Connection : END

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
} /// Add_Contained : END

void Zone::Remove_Contained(Cell* cell) {
    int i = 0;
    for (; i < number_of_contained; i++)
        if (contained[i] == cell)
            break;

    if (i == number_of_contained)
        return;

    contained[i] = contained[number_of_contained - 1];
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

    // I have to check whether this contained cell was a connection to some neighbour
    for (int j = 0; j < number_of_neighbours; j++) {
        for (int k = 0; k < number_of_connections[j]; k++) {
            if (connections[j][k] == cell) {
                Remove_Connection(neighbours[j], connections[j][k]);
            }
        }
    } // for : j
} /// Remove_Contained : END

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
} /// Add_Neighbour : END

void Zone::Remove_Neighbour(Cell* cell) {
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
} /// Remove_Neighbour : END

bool Zone::Fragment(Cell***& subzones, int*& number_of_subzones_elements, int& number_of_subzones) {
    /* First I reset the state of the variables that I fill with data and create a copy of cells
     * contained in the zone that I can safely manipulate without changing the original array */
    for (int i = 0; i < number_of_subzones; i++)
        delete[] subzones[i];
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

        subzones[number_of_subzones][0] = head_contained_copy->payload;
        number_of_subzones_elements[number_of_subzones] = 1;
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

        /* For each cell that is currently in the subzone, I check if all of its neighbours are placed,
         * if they are not they are added into the subzone. However, if they are not members of the
         * zone (they are neighbours in another zone, connections) they are not added */
        for (int i = 0; i < number_of_subzones_elements[number_of_subzones]; i++) {
            auto neighbours = subzones[number_of_subzones][i]->Get_Neighbours();
            bool already_placed = false;

            for (int j = 0; j < subzones[number_of_subzones][i]->Get_Number_Of_Neighbours(); j++) {

                for (int k = 0; k < number_of_subzones_elements[number_of_subzones]; k++) {
                    if (neighbours[i] == subzones[number_of_subzones][k]) {
                        already_placed = true;
                        break;
                    }
                } // for : k

                if (!already_placed) {
                    auto follower = head_contained_copy;

                    for (auto iterator = head_contained_copy; iterator != nullptr; iterator = iterator->next) {
                        if (neighbours[i] == iterator->payload) {

                            if (number_of_subzones_elements[number_of_subzones] % CHUNK == 0) {
                                auto replace_subzone = new Cell*[number_of_subzones_elements[number_of_subzones] + CHUNK];

                                for (int l = 0; l < number_of_subzones_elements[number_of_subzones]; l++) {
                                    replace_subzone[l] = subzones[number_of_subzones][l];
                                    subzones[number_of_subzones][l] = nullptr;
                                }
                                delete[] subzones[number_of_subzones];
                                subzones[number_of_subzones] = replace_subzone;
                            }
                            number_of_subzones_elements[number_of_subzones] += 1;
                            subzones[number_of_subzones][number_of_subzones_elements[number_of_subzones]] = neighbours[i];

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
                        } // if : neighbours[i]

                        follower = iterator;
                    }// for : iterator
                } // if : !already_placed

            } // for : j
        } // for : i

        number_of_subzones += 1;
    } // while (head_contained_copy != nullptr)

    return (number_of_subzones > 1);
} /// Fragment : END

void Zone::Replace(Cell* cell, Cell*** subzones, int* number_of_subzones_elements, int number_of_subzones) {
    /* Firstly, I get all the neighbours of the cell to be removed, and all of their connections to this zone.
     * That is because these connections are connections that will be distributed over subzones without any
     * excess or lacking. Also because zone is to be destroyed, it is removed from all its neighbours */
    int cell_number_of_neighbours = cell->Get_Number_Of_Neighbours();
    auto cell_neighbours = cell->Get_Neighbours();
    auto neighbours_number_of_connections_to_cell = new int[cell_number_of_neighbours];
    auto neighbours_connections_to_cell = new Cell**[cell_number_of_neighbours];
    for (int i = 0; i < cell_number_of_neighbours; i++) {
        auto neighbour_connections_copy = cell_neighbours[i]->Get_Connections(cell);
        neighbours_number_of_connections_to_cell[i] = cell_neighbours[i]->Get_Number_Of_Connections(cell);

        neighbours_connections_to_cell[i] = new Cell*[neighbours_number_of_connections_to_cell[i]];
        for (int j = 0; j < neighbours_number_of_connections_to_cell[i]; j++)
            neighbours_connections_to_cell[i][j] = neighbour_connections_copy[j];

        cell_neighbours[i]->Remove_Neighbour(cell);
    } // for : i

    /* Secondly, remove all connections zones neighbours have to this zone,
     * then finally remove the cell from the zone, clean and delete it. Also
     * I save some relevant information of the cell for later */
    const int x = cell->Get_X();
    const int y = cell->Get_Y();
    const int level = cell->Get_Level();
    const int cell_num_neighbours_for_deletion = cell_number_of_neighbours;
    for (int i = 0; i < number_of_neighbours; i++) {
        for (int j = 0; j < number_of_connections[i]; j++) {
            if (connections[i][j] == cell) {
                if (Cell* connection = neighbours[i]->Adjacent_Vertical(x, y))
                    neighbours[i]->Remove_Connection(this, connection);

                if (Cell* connection = neighbours[i]->Adjacent_Horizontal(x, y))
                    neighbours[i]->Remove_Connection(this, connection);
            }
        }
    } // for : i
    Remove_Contained(cell);
    cell->Wipe_Clean();
    delete cell;

    /* Finally, subzones are properly created and filled, then connected to neighbouring zones */
    for (int i = 0; i < number_of_subzones; i++) {
        auto subzone = new Zone(x, y, level, 0, true);
        Add_Contained(subzone);

        for (int j = 0; j < number_of_subzones_elements[i]; j++) {
            subzone->Add_Contained(subzones[i][j]);
            subzone->Update_Capacity(subzones[i][j]->Get_Capacity());

            for (int m = 0; m < cell_number_of_neighbours; m++) {
                for (int n = 0; n < neighbours_number_of_connections_to_cell[m]; n++) {
                    if (Cell::Are_Adjacent(subzones[i][j], neighbours_connections_to_cell[m][n])) {
                        Make_Neighbours(subzone, cell_neighbours[m], subzones[i][j], neighbours_connections_to_cell[m][n]);
                        Make_Neighbours(this, cell_neighbours[m]->Get_Container(), subzone, cell_neighbours[m]);

                        for (int k = n; k < neighbours_number_of_connections_to_cell[m] - 1; k++)
                            neighbours_connections_to_cell[m][k] = neighbours_connections_to_cell[m][k + 1];
                        neighbours_connections_to_cell[m][neighbours_number_of_connections_to_cell[m] - 1] = nullptr;
                        neighbours_number_of_connections_to_cell[m] -= 1;
                        n -= 1;

                        if (neighbours_number_of_connections_to_cell[m] == 0) {
                            for (int k = m; k < cell_number_of_neighbours - 1; k++) {
                                cell_neighbours[k] = cell_neighbours[k + 1];
                                neighbours_number_of_connections_to_cell[k] = neighbours_number_of_connections_to_cell[k + 1];
                                neighbours_connections_to_cell[k] = neighbours_connections_to_cell[k + 1];
                            }
                            cell_neighbours[cell_number_of_neighbours - 1] = nullptr;
                            cell_number_of_neighbours -= 1;
                            m -= 1;
                        }
                    } // if : Cell::Are_Adjacent
                }
            }

            subzones[i][j] = nullptr;
        } // for : j

    } // for : i

    delete[] neighbours_number_of_connections_to_cell;
    for (int i = 0; i < cell_num_neighbours_for_deletion; i++)
        delete[] neighbours_connections_to_cell[i];
    delete[] neighbours_connections_to_cell;
} /// Replace : END

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
} /// Wipe_Clean : END

bool Zone::Find_Path(Cell** starting_positions, int first_array_size, Cell** destination_positions, int second_array_size) {

} /// Find_Path : END

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
} /// ~Zone : END