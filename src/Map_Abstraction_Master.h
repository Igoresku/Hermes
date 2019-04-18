//
// Created by Igor Duric on 4/18/19.
//

#ifndef PATH_FINDING_MAP_ABSTRACTION_MASTER_H
#define PATH_FINDING_MAP_ABSTRACTION_MASTER_H

#include "../include/Zone.h"
#include "../include/Game_Map.h"

class Map_Abstraction_Master {
public:
    // creates the hierarchy of abstractions for a single map (which is made for single traversal type) and its dimensions
    void Create_Abstraction(Game_Map*, int, Traversal_Type);

private:
    Cell* map_abstractions[3] = { nullptr, nullptr, nullptr };
    int hierarchy_size = 0;
};


#endif //PATH_FINDING_MAP_ABSTRACTION_MASTER_H
