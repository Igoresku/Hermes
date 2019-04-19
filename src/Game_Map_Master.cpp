//
// Created by Igor Duric on 4/17/19.
//

#include "../include/Game_Map_Master.h"

Game_Map_Master* Game_Map_Master::Factory(std::string file_name) {
    std::ifstream input_File;
    input_File.open(file_name);
    if (!input_File) { // to be replaced by throwing an exception
        std::cout << "Unsuccessful read: File does not exist\n";
        return nullptr;
    }

    int dimensions, abstraction_size, max_agent_size;
    input_File >> dimensions;
    input_File >> abstraction_size;
    input_File >> max_agent_size;
    auto raw_map = new int*[dimensions];
    for (int i = 0; i < dimensions; )
        raw_map[i++] = new int[dimensions];

    int a = abstraction_size;
    for (; a < dimensions; ) a = a * a;

    if (a != dimensions) {
        // to be replaced by throwing an exception
        std::cout << "Unsuccessful read: File is in invalid format (this abstraction size: " << abstraction_size
        << " cannot be paired with these dimensions: " << dimensions << ")\n";
        return nullptr;
    }

    char read_data;
    for (int i = 0; i < dimensions; i++) {
        for (int j = 0; j < dimensions; j++) {
            input_File >> read_data;
            switch (read_data) {
                case '_': {
                    raw_map[i][j] = 0;
                    break;
                }

                case '~': {
                    raw_map[i][j] = 1;
                    break;
                }

                case '^': {
                    raw_map[i][j] = 2;
                    break;
                }

                default: {
                    for (int k = 0; k < dimensions; )
                        delete raw_map[k++];
                    delete[] raw_map;

                    // to be replaced by throwing an exception
                    std::cout << "Unsuccessful read: File is in invalid format (unknown symbol: " << read_data << ")\n";
                    return nullptr;
                }
            } // switch : read_data

        } // for : j
    } // for : i

    return new Game_Map_Master(dimensions, abstraction_size, max_agent_size, raw_map);
}

Game_Map_Master::Game_Map_Master(int dimensions, int abstraction_size, int max_agent_size, int** raw_map)
    : dimensions(dimensions), abstraction_size(abstraction_size), max_agent_size(max_agent_size), raw_map(raw_map) {
}

void* Game_Map_Master::run() {
    maps[0] = new Game_Map(raw_map, dimensions, max_agent_size, Traversal_Type::Walking);
    maps[1] = new Game_Map(raw_map, dimensions, max_agent_size, Traversal_Type::Swimming);

    for (int i = 0; i < dimensions; )
        delete[] raw_map[i++];
    delete[] raw_map;

    map_abstraction_master = new Map_Abstraction_Master(dimensions, abstraction_size);
    map_abstraction_master->Create_Abstraction(maps[0], Traversal_Type::Walking);
    map_abstraction_master->Create_Abstraction(maps[1], Traversal_Type::Swimming);

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