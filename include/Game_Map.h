//
// Created by Igor Duric on 4/14/19.
//

#ifndef PATH_FINDING_GAME_MAP_H
#define PATH_FINDING_GAME_MAP_H

#include "Traversal_Type.h"

class Game_Map {
public:
    Game_Map(int**, int, int, Traversal_Type);

    Game_Map(const Game_Map&) = delete;
    Game_Map(Game_Map&&) = delete;

private:
    int** map;
}; // class Game_Map


#endif //PATH_FINDING_GAME_MAP_H