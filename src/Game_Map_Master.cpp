//
// Created by Igor Duric on 4/17/19.
//

#include "../include/Game_Map_Master.h"

void* Game_Map_Master::run() {
    std::ifstream input_File;
    input_File.open(file_name);

    input_File >> dimensions;
    input_File >> max_agent_size;
    auto map = new int*[dimensions];
    for (int i = 0; i < dimensions; )
        map[i++] = new int[dimensions];

    char read_data;
    for (int i = 0; i < dimensions; i++) {
        for (int j = 0; j < dimensions; j++) {
            input_File >> read_data;
            switch (read_data) {
                case '_': {
                    map[i][j] = 0;
                    break;
                }

                case '~': {
                    map[i][j] = 1;
                    break;
                }

                case '^': {
                    map[i][j] = 2;
                    break;
                }

                default: ;
                    // abort
            } // switch : read_data

        } // for : j
    } // for : i

    maps[0] = new Game_Map(map, dimensions, max_agent_size, Traversal_Type::Walking);
    maps[1] = new Game_Map(map, dimensions, max_agent_size, Traversal_Type::Swimming);

    for (int i = 0; i < dimensions; )
        delete[] map[i++];
    delete[] map;

    return nullptr;
}

void Game_Map_Master::Add_Agent(int size, Traversal_Type traversal_type, int x, int y) {

    if (number_of_agents % 10 == 0) {
        auto replace_array = new Agent*[number_of_agents + 10];
        for (int i = 0; i < number_of_agents + 10; i++) {
            replace_array[i] = (i < number_of_agents) ? agents[i] : nullptr;
            agents[i] = nullptr;
        }
        delete[] agents;
        agents = replace_array;
    }

    agents[number_of_agents++] = new Agent(size, traversal_type, x, y);
}

void Game_Map_Master::List_All_Agents() {
    for (int i = 0; i < number_of_agents; i++)
        std::cout << "Agent number[" << i << "] has size: " << agents[i]->Get_Size()
                  << "; and traversal type: " << Print_Traversal_Type(agents[i]->Get_Traversal_Type())
                  << "; and coordinates: " << agents[i]->Get_X() << ", " << agents[i]->Get_Y() << "\n";
}