//
// Created by Igor Duric on 4/18/19.
//

#include "../include/Map_Abstraction_Master.h"

Map_Abstraction_Master::Map_Abstraction_Master(int dimensions, int abstraction_size) : dimensions(dimensions), abstraction_size(abstraction_size) {
    hierarchy_size = 0;
    for (int i = dimensions; i > 1; i /= abstraction_size)
        hierarchy_size += 1;
}

void Map_Abstraction_Master::Make_Neighbours(Cell* first, Cell* second) {
    first->Add_Neighbour(second);
    second->Add_Neighbour(first);
}

void Map_Abstraction_Master::Make_Neighbours(Cell* first, Cell* second, Cell* connection_1, Cell* connection_2) {
    Make_Neighbours(first, second);
    first->Add_Connection(second, connection_1);
    second->Add_Connection(first, connection_2);
}

void Map_Abstraction_Master::Create_Abstraction(Game_Map* game_map, Traversal_Type&& traversal_type) {
    /* First step is creating a matrix of series of abstractions, this will allow me to
     * very neatly create and interweave them by creating the lowest level, and then
     * propagate that creation upwards, creating the upper levels as needed */
    Cell**** current_map_abstractions = new Cell***[hierarchy_size];
    for (int i = 0, matrix_size = abstraction_size; i < hierarchy_size; i++, matrix_size *= abstraction_size) {
        current_map_abstractions[i] = new Cell**[matrix_size];

        for (int j = 0; j < matrix_size; j++) {
            current_map_abstractions[i][j] = new Cell*[matrix_size];
            // next step of the algorithm will initialize the lowest level as a side-effect
            if (i != hierarchy_size - 1)
                for (int k = 0; k < matrix_size; k++)
                    current_map_abstractions[i][j][k] = nullptr;

        } // for : j
    } // for : i

    /* Now, I analyze the map and create cells of abstraction as I come across passable terrain,
     * this creation then propagates upwards through the levels of abstraction and creates them
     * as necessary. Also as cells and zones are created they are linked to those created
     * previously and who might be concerned for adjacency's sake */
    auto first_level_abstraction = current_map_abstractions[hierarchy_size-1];
    int max_capacity = 0;
    for (int i = 0; i < dimensions; i++) {
        for (int j = 0; j < dimensions; j++) {

            if (game_map->Cell_Passable(i, j)) {
                int cell_capacity = game_map->Get_Cell_Content(i, j);
                if (cell_capacity > max_capacity)
                    max_capacity = cell_capacity;

                first_level_abstraction[i][j] = new Cell(i, j, 0, cell_capacity);
                // neighbouring west and north cells are connected, if such cells exist
                if (i != 0) if (first_level_abstraction[i-1][j] != nullptr)
                    Make_Neighbours(first_level_abstraction[i][j], first_level_abstraction[i-1][j]);

                if (j != 0) if (first_level_abstraction[i][j-1] != nullptr)
                    Make_Neighbours(first_level_abstraction[i][j], first_level_abstraction[i][j-1]);

                // I travel upwards through levels of abstraction, and notify relevant zones of cells creation
                int m = i / abstraction_size, n = j / abstraction_size, prev_m = i, prev_n = j;
                for (int level = hierarchy_size - 2; level >= 0; level--) {
                    if (current_map_abstractions[level][m][n] == nullptr)
                        current_map_abstractions[level][m][n] = new Zone(m, n, hierarchy_size-level-1, cell_capacity);
                    else
                        current_map_abstractions[level][m][n]->Update_Capacity(cell_capacity);

                    current_map_abstractions[level][m][n]->Add_Contained(
                            current_map_abstractions[level+1][prev_m][prev_n]);
                    // neighbouring west and north zones are connected, if such zones exist
                    // also, connections between them are identified
                    if (m != 0) if (current_map_abstractions[level][m-1][n] != nullptr)
                        if (Cell* connection = current_map_abstractions[level][m-1][n]->Adjacent_South(m, n))
                            Make_Neighbours(current_map_abstractions[level][m][n], current_map_abstractions[level][m-1][n],
                                    connection, current_map_abstractions[level+1][prev_m][prev_n]);

                    if (n != 0) if (current_map_abstractions[level][m][n-1] != nullptr)
                        if (Cell* connection = current_map_abstractions[level][n][n-1]->Adjacent_East(m, n))
                            Make_Neighbours(current_map_abstractions[level][m][n], current_map_abstractions[level][m][n-1],
                                    connection, current_map_abstractions[level+1][prev_m][prev_n]);

                    prev_m = m;
                    prev_n = n;
                    m = m / abstraction_size;
                    n = n / abstraction_size;
                } // for : level
            } else {
                first_level_abstraction[i][j] = nullptr;
            } // if : game_map->Get_Cell_Content(i, j)

        } // for : j
    } // for : i

    /* Finally, I create the highest-level abstraction and populate it with highest-level zones */
    map_abstractions[(int)traversal_type] = new Map_Abstraction(0, 0, hierarchy_size, max_capacity);
    for (int i = 0; i < abstraction_size; i++)
        for (int j = 0; j < abstraction_size; j++)
            if (current_map_abstractions[0][i][j] != nullptr)
                current_map_abstractions[0][i][j]->Set_Container(map_abstractions[(int)traversal_type]);

    // TODO: now that the map is made, it has to be run through again and checked if there are zones that have their sub-zones divided by terrain
}

