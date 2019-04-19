//
// Created by Igor Duric on 4/18/19.
//

#include "../include/Map_Abstraction_Master.h"

Map_Abstraction_Master::Map_Abstraction_Master(int dimensions) : dimensions(dimensions) {
    // i calculate the number of abstraction levels, which are made of 8x8 zones of cells
    hierarchy_size = 0;
    for (int i = dimensions; i > 1; i /= 8)
        hierarchy_size += 1;
}

void Map_Abstraction_Master::Create_Abstraction(const Game_Map*& game_map, Traversal_Type&& traversal_type) {

    /* First step is creating a matrix of series of abstractions, this will allow me to
     * very neatly create and interweave them by creating the lowest level, and then
     * propagate that creation upwards, creating the upper level as needed */
    Cell**** current_map_abstractions = new Cell***[hierarchy_size];
    for (int i = 0, current_matrix_size = 8; i < hierarchy_size; i++, current_matrix_size *= 8) {
        current_map_abstractions[i] = new Cell**[current_matrix_size];

        for (int j = 0; j < current_matrix_size; j++) {
            current_map_abstractions[i][j] = new Cell*[current_matrix_size];
            // i do not want to initialize the lowest level abstraction,
            // next step of the algorithm will do it as a side-effect
            if (i != hierarchy_size - 1)
                for (int k = 0; k < current_matrix_size; )
                    current_map_abstractions[i][j][k++] = nullptr;

        } // for : j
    } // for : i

    /* auto cached_horizontal = new Cell*[hierarchy_size];
    for (int i = 0; i < hierarchy_size; )
        cached_horizontal[i++] = nullptr;

    auto cached_vertical = new Cell**[hierarchy_size];
    for (int i = 0; i < hierarchy_size; i++) {

    } */

    /* Now, I analyze the map and create cells of abstraction as I come across passable terrain,
     * this creation then propagates upwards through the levels of abstraction and creates them
     * as necessary. Also as cells and zones are created they are linked to those created
     * previously and who might be concerned for adjacency's sake */
    auto first_level_abstraction = current_map_abstractions[hierarchy_size - 1];
    for (int i = 0; i < dimensions; i++) {
        for (int j = 0; j < dimensions; j++) {

            if (game_map->Cell_Passable(i, j)) {
                int cell_capacity = game_map->Get_Cell_Content(i, j);
                first_level_abstraction[i][j] = new Cell(i, j, cell_capacity);
                // the cell finds the nearest north and west cells and they add each other as neighbours, if such cells exists
                for (int m = i - 1; m >= 0; m--) {
                    if (first_level_abstraction[m][j] != nullptr) {
                        first_level_abstraction[m][j]->Add_Neighbour(first_level_abstraction[i][j]);
                        first_level_abstraction[i][j]->Add_Neighbour(first_level_abstraction[m][j]);
                        break;
                    }
                } // for : m

                for (int m = j - 1; m >= 0; m--) {
                    if (first_level_abstraction[i][m] != nullptr) {
                        first_level_abstraction[i][m]->Add_Neighbour(first_level_abstraction[i][j]);
                        first_level_abstraction[i][j]->Add_Neighbour(first_level_abstraction[i][m]);
                        break;
                    }
                } // for : m

                int m = i / 8, n = j / 8, previous_m = i, previous_n = j;
                for (int level = hierarchy_size - 2; level >= 0; level--) {
                    if (current_map_abstractions[level][m][n] == nullptr)
                        current_map_abstractions[level][m][n] = new Zone(m, n, cell_capacity);
                    else
                        current_map_abstractions[level][m][n]->Update_Capacity(cell_capacity);

                    current_map_abstractions[level+1][previous_m][previous_n]->Set_Container(current_map_abstractions[level][m][n]);

                    // same as above where cell is searching for its neighbours, zone performs the same on its level
                    for (int k = m - 1; k >= 0; k--) {
                        if (current_map_abstractions[level][k][n] != nullptr) {
                            current_map_abstractions[level][k][n]->Add_Neighbour(current_map_abstractions[level][m][n]);
                            current_map_abstractions[level][m][n]->Add_Neighbour(current_map_abstractions[level][k][n]);
                            break;
                        }
                    } // for : k

                    for (int k = n - 1; k >= 0; k--) {
                        if (current_map_abstractions[level][m][k] != nullptr) {
                            current_map_abstractions[level][m][k]->Add_Neighbour(current_map_abstractions[level][m][m]);
                            current_map_abstractions[level][m][n]->Add_Neighbour(current_map_abstractions[level][m][k]);
                            break;
                        }
                    } // for : k

                    // takodje add u contained i connected, treba provera za to !!!
                    previous_m = m;
                    previous_n = n;
                    m = m / 8;
                    n = n / 8;
                } // for : level
            } else {
                first_level_abstraction[i][j] = nullptr;
            } // if : game_map->Get_Cell_Content(i, j)

        } // for : j
    } // for : i

    // map_abstractions[(int)traversal_type] = new Zone(0, 0);
}