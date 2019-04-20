//
// Created by Igor Duric on 4/17/19.
//

#ifndef PATH_FINDING_GAME_MAP_MASTER_H
#define PATH_FINDING_GAME_MAP_MASTER_H

#include <fstream>
#include "Runnable.h"
#include "Game_Map.h"
#include "Agent.h"
#include "Map_Abstraction_Master.h"
#include "Nonexistent_File.h"
#include "Invalid_File_Format.h"

class Game_Map_Master : public Runnable {
public: // meta
    static Game_Map_Master* Factory(std::string) noexcept(false);
public:
    void Add_Agent(int, Traversal_Type, int, int);
    void List_All_Agents();

    ~Game_Map_Master() override = default;
protected:
    Game_Map_Master(int, int, int, int**);

    void* run() override;

private:
    int dimensions;
    int abstraction_size;
    int max_agent_size;
    Agent** agents = nullptr;
    int number_of_agents = 0;

    int** raw_map;
    Game_Map* maps[2] = { nullptr, nullptr };
    Map_Abstraction_Master* map_abstraction_master;
}; // class Game_Map_Master

// trenutno provera postojanja fajla i njegovog formata obavlja u konstruktoru, sto semanticki nije ispravno
// ovo treba rijesiti factory metodom koja ce da izvrsi provjeru, i ako je sve u redu sa fajlom vratiti instancu objekta

#endif //PATH_FINDING_GAME_MAP_MASTER_H
