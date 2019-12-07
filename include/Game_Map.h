//
// Created by Igor Duric on 4/14/19.
//

#ifndef PATH_FINDING_GAME_MAP_H
#define PATH_FINDING_GAME_MAP_H

#include <cstdint>
#include "Employer.h"
#include "Terrain.h"

class Game_Map : public Employer {
public:
    explicit Game_Map(int = 8);

    Game_Map(const Game_Map&) = delete;
    Game_Map(Game_Map&&) = delete;


    bool Cell_Passable(int x, int y) const { return (map[x/4][y/4] & (0xC0 >> ((y%4)*2))) != 0; } //
    int Get_Cell_Content(int x, int y) const { return (map[x/4][y/4] >> ((3-(y%4))*2)) & 0x03; } //
private:
    unsigned char** raw_map;
    int dimensions;
    bool initialized = false;
}; // class Game_Map


#endif //PATH_FINDING_GAME_MAP_H
