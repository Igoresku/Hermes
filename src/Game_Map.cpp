//
// Created by Igor Duric on 4/14/19.
//

#include "../include/Game_Map.h"

Game_Map::Game_Map(int** raw_map, int dimensions, int max_agent_size, Traversal_Type traversal_type) {
    this->map = new int*[dimensions];
    for (int i = 0; i < dimensions; i++)
        this->map[i] = new int[dimensions];

    for (int i = 0; i < dimensions; i++) {
        for (int j = 0; j < dimensions; j++) {
            // i check if cell is passable at all for given traversal type
            if (raw_map[i][j] <= (int)traversal_type) {
                bool failed = false;

                this->map[i][j] = 1;
                // i check if agent of size agent_size can fit into this spot
                for (int agent_size = 1; agent_size < max_agent_size; agent_size++) {
                    if ((i + agent_size >= dimensions) || (j + agent_size >= dimensions))
                        break;

                    for (int m = 1; m <= agent_size; m++) {
                        if (raw_map[i + agent_size][j + m] > (int)traversal_type) {
                            failed = true;
                            break;
                        }
                    } // for : m

                    if (failed)
                        break;

                    for (int m = 1; m <= agent_size; m++) {
                        if (raw_map[i + m][j + agent_size] > (int)traversal_type) {
                            break;
                        }
                    } // for : m

                    this->map[i][j]++;
                } // for : agent_size
            } else {
                // terrain is set to impassable for this traversal type
                this->map[i][j] = -1;
            }// if : map[i][j]

        } // for : j
    }// for : i

};// Game_Map constructor

