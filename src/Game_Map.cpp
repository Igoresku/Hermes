//
// Created by Igor Duric on 4/14/19.
//

#include "../include/Game_Map.h"

Game_Map::Game_Map(uint8_t** raw_map, int dimensions, int max_agent_size, Traversal_Type traversal_type) {
    map = new uint8_t*[dimensions / 4];
    for (int i = 0; i < dimensions / 4; i++)
        map[i] = new uint8_t[dimensions / 4];

    for (int i = 0; i < dimensions / 4; i++) {
        for (int j = 0; j < dimensions / 4; j++) {
            uint8_t content = raw_map[i/4][j/4] >> ((3-(j%4))*2);
            content &= 0x03;

            if (content <= (int)traversal_type) {
                bool failed = false;

                uint8_t value = 1;
                // I use rectangular clearance to calculate the max agent size that can fit into this cell
                for (int agent_size = 1; agent_size < max_agent_size; agent_size++) {
                    if ((i + agent_size >= dimensions) || (j + agent_size >= dimensions))
                        break;

                    for (int m = 1; m <= agent_size; m++) {
                        content = raw_map[(i+agent_size)/4][(j+m)/4] >> ((3-(j%4))*2);
                        content &= 0x03;
                        if (content > (int)traversal_type) {
                            failed = true;
                            break;
                        }
                    } // for : m

                    if (failed)
                        break;

                    for (int m = 1; m <= agent_size; m++) {
                        content = raw_map[(i+m)/4][(j+agent_size)/4] >> ((3-(j%4))*2);
                        content &= 0x03;
                        if (content > (int)traversal_type) {
                            failed = true;
                            break;
                        }
                    } // for : m

                    if (failed)
                        break;

                    value++;
                } // for : agent_size
                map[i/4][j/4] |= value << ((3-(j%4))*2);
            } else {
                // terrain is set to impassable for this traversal type
                map[i/4][j/4] &= 0x3F >> ((j%4)*2);
            }// if : map[i][j]

        } // for : j
    }// for : i

} /// Game_Map : END

