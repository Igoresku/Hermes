//
// Created by Igor Duric on 4/1abstraction_size/19.
//

#include "../include/Map_Abstraction_Master.h"

Map_Abstraction_Master::Map_Abstraction_Master(int dimensions, int abstraction_size) : dimensions(dimensions), abstraction_size(abstraction_size) {
    hierarchy_size = 0;
    for (int i = dimensions; i > 1; i /= abstraction_size)
        hierarchy_size += 1;
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
                for (int k = 0; k < matrix_size; )
                    current_map_abstractions[i][j][k++] = nullptr;

        } // for : j
    } // for : i

    /* Now, I analyze the map and create cells of abstraction as I come across passable terrain,
     * this creation then propagates upwards through the levels of abstraction and creates them
     * as necessary. Also as cells and zones are created they are linked to those created
     * previously and who might be concerned for adjacency's sake */
    auto first_level_abstraction = current_map_abstractions[hierarchy_size-1];
    for (int i = 0; i < dimensions; i++) {
        for (int j = 0; j < dimensions; j++) {

            if (game_map->Cell_Passable(i, j)) {
                int cell_capacity = game_map->Get_Cell_Content(i, j);
                first_level_abstraction[i][j] = new Cell(i, j, cell_capacity);

                // neighbouring west and north cells are connected, if such cells exist
                if (i != 0) if (first_level_abstraction[i-1][j] != nullptr) {
                    first_level_abstraction[i][j]->Add_Neighbour(first_level_abstraction[i-1][j]);
                    first_level_abstraction[i-1][j]->Add_Neighbour(first_level_abstraction[i][j]);
                }

                if (j != 0) if (first_level_abstraction[i][j-1] != nullptr) {
                    first_level_abstraction[i][j]->Add_Neighbour(first_level_abstraction[i][j-1]);
                    first_level_abstraction[i][j-1]->Add_Neighbour(first_level_abstraction[i][j]);
                }

                int m = i / abstraction_size, n = j / abstraction_size, previous_m = i, previous_n = j;
                for (int level = hierarchy_size - 2; level >= 0; level--) {
                    if (current_map_abstractions[level][m][n] == nullptr)
                        current_map_abstractions[level][m][n] = new Zone(m, n, cell_capacity);
                    else
                        current_map_abstractions[level][m][n]->Update_Capacity(cell_capacity);

                    current_map_abstractions[level+1][previous_m][previous_n]->Set_Container(
                            current_map_abstractions[level][m][n]);

                    // adjacency is trivial with cells, but not with zones
                    if (m != 0) if (current_map_abstractions[level][m-1][n] != nullptr)
                        if (Cell* connection = current_map_abstractions[level][m-1][n]->Adjacent_South(m, n)) {
                            current_map_abstractions[level][m][n]->Add_Neighbour(
                                    current_map_abstractions[level][m - 1][n]);
                            current_map_abstractions[level][m - 1][n]->Add_Neighbour(
                                    current_map_abstractions[level][m][n]);
                            // the lower level connections between zones are identified
                            current_map_abstractions[level][m][n]->Add_Connection(
                                    current_map_abstractions[level][m - 1][n], connection);
                            current_map_abstractions[level][m - 1][n]->Add_Connection(
                                    current_map_abstractions[level][m][n],
                                    current_map_abstractions[level-1][previous_m][previous_n]);
                        }

                    if (n != 0) if (current_map_abstractions[level][m][n-1] != nullptr)
                        if (Cell* connection = current_map_abstractions[level][n][n-1]->Adjacent_East(m, n)) {
                            current_map_abstractions[level][m][n]->Add_Neighbour(
                                    current_map_abstractions[level][m][n - 1]);
                            current_map_abstractions[level][m][n - 1]->Add_Neighbour(
                                    current_map_abstractions[level][m][n]);
                            // the lower level connections between zones are identified
                            current_map_abstractions[level][m][n]->Add_Connection(
                                    current_map_abstractions[level][m][n-1], connection);
                            current_map_abstractions[level][m][n-1]->Add_Connection(
                                    current_map_abstractions[level][m][n],
                                    current_map_abstractions[level-1][previous_m][previous_n]);
                        }

                    previous_m = m;
                    previous_n = n;
                    m = m / abstraction_size;
                    n = n / abstraction_size;
                } // for : level
            } else {
                first_level_abstraction[i][j] = nullptr;
            } // if : game_map->Get_Cell_Content(i, j)

        } // for : j
    } // for : i

    // map_abstractions[(int)traversal_type] = new Zone(0, 0);
}
