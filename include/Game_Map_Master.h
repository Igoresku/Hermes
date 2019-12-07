//
// Created by Igor Duric on 4/17/19.
//

#ifndef PATH_FINDING_GAME_MAP_MASTER_H
#define PATH_FINDING_GAME_MAP_MASTER_H

#include <fstream>
#include <cstdint>
#include "Runnable.h"
#include "Employer.h"
#include "Game_Map.h"
#include "Agent.h"
#include "Map_Abstraction.h"
#include "Nonexistent_File.h"

class Game_Map_Master : public Employer {
public:

    ~Game_Map_Master() override = default;
protected:
    Game_Map_Master(int, int, int, uint8_t**);



private:
    int dimensions;
    int abstraction_size;
    int max_agent_size;
    Agent** agents = nullptr;
    int number_of_agents = 0;

    uint8_t** raw_map;
    Game_Map* maps[2] = { nullptr, nullptr };
    Map_Abstraction* map_abstraction_master;
}; // class Game_Map_Master

#endif //PATH_FINDING_GAME_MAP_MASTER_H
