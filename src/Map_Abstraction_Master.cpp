//
// Created by Igor Duric on 4/18/19.
//

#include "Map_Abstraction_Master.h"

void Map_Abstraction_Master::Create_Abstraction(Game_Map* game_map, int dimensions, Traversal_Type traversal_type) {
    for (int i = dimensions; i > 1; i /= 8)
        hierarchy_size += 1;

    map_abstractions[(int)traversal_type] = new Zone(0, 0, hierarchy_size);

    // i create the first level of abstraction from the original map
    Cell*** first_level_abstraction = new Cell**[dimensions];
    for (int i = 0; i < dimensions; )
        first_level_abstraction[i++] = new Cell*[dimensions];

    for (int i = 0; i < dimensions; i++) {
        for (int j = 0; j < dimensions; j++) {
            // i check if a cell in this place should exist, i.e is this tile passable
            if (game_map->Get_Cell_Content(i, j) != 0) {
                first_level_abstraction[i][j] = new Cell(i, j);
                // the cell finds the nearest upwards cell and they add each other as neighbours, if such a cell exists
                for (int m = i; m >= 0; m--) {
                    if (first_level_abstraction[m][j] != nullptr) {
                        first_level_abstraction[m][j]->Add_Neighbour(first_level_abstraction[i][j]);
                        first_level_abstraction[i][j]->Add_Neighbour(first_level_abstraction[m][j]);
                        break;
                    }
                } // for : m

                // the cell finds the nearest left cell and they add each other as neighbours, if such a cell exists
                for (int m = j; m >= 0; m--) {
                    if (first_level_abstraction[i][m] != nullptr) {
                        first_level_abstraction[i][m]->Add_Neighbour(first_level_abstraction[i][j]);
                        first_level_abstraction[i][j]->Add_Neighbour(first_level_abstraction[i][m]);
                        break;
                    }
                } // for : m
            } else {
                // cell in the place of this tile does not exist
                first_level_abstraction[i][j] = nullptr;
            } // if : game_map->Get_Cell_Content(i, j)

        } // for : j
    } // for : i

    Cell*** next_level_of_abstraction = new Cell**[dimensions / 8];
    for (int i = 0; i < dimensions / 8; )
        next_level_of_abstraction[i++] = new Cell*[dimensions / 8];

    for (int i = 0)

}