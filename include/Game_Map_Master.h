//
// Created by Igor Duric on 4/17/19.
//

#ifndef PATH_FINDING_GAME_MAP_MASTER_H
#define PATH_FINDING_GAME_MAP_MASTER_H

#include <pthread.h>
#include <fstream>
#include "Runnable.h"
#include "Game_Map.h"
#include "Agent.h"

class Game_Map_Master : public Runnable {
public:
    explicit Game_Map_Master(std::string& file_name) : file_name(file_name) {};

    void Add_Agent(int, Traversal_Type, int, int);
    void List_All_Agents();

    ~Game_Map_Master() override = default;
protected:
    void* run() override;

private:
    int dimensions = 0;
    int max_agent_size = 0;
    std::string file_name;

    Game_Map* maps[3] = { nullptr, nullptr, nullptr };
    Agent** agents = nullptr;
    int number_of_agents = 0;
}; // class Game_Map_Master


#endif //PATH_FINDING_GAME_MAP_MASTER_H
