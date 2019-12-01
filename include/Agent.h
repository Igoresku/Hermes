//
// Created by Igor Duric on 4/16/19.
//

#ifndef PATH_FINDING_AGENT_H
#define PATH_FINDING_AGENT_H

#include <iostream>
#include "Terrain.h"

/** Agent represents a unit that is placed and moves on the map,
 * it is represented by its size(?) and terrain it can traverse */
class Agent {
public:
    Agent(int size, Traversal_Type traversal_type, int x, int y) : size(size), traversal_type(traversal_type), x(x), y(y) {};
    Agent(const Agent&) = delete;
    Agent(Agent&&) = delete;

    int Get_Size() const { return size; }
    Traversal_Type  Get_Traversal_Type() const { return traversal_type; }
    int Get_X() const { return x; }
    int Get_Y() const { return y; }
private:
    const int size;
    const Traversal_Type traversal_type;
    int x;
    int y;
};
// u implementaciji agenta ili game_map_mastera ne postoji informacija o lokaciji agenta na mapi, to je potrebno da se ispravi

#endif //PATH_FINDING_AGENT_H
