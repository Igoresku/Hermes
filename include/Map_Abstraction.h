//
// Created by Igor Duric on 4/18/19.
//

#ifndef PATH_FINDING_MAP_ABSTRACTION_MASTER_H
#define PATH_FINDING_MAP_ABSTRACTION_MASTER_H

#include "Map_Abstraction_Level.h"
#include "Game_Map.h"

class Map_Abstraction {
public:
    explicit Map_Abstraction(int, int = 8);

    void Create_Abstraction(Game_Map*, Traversal_Type&&);
private:
    Cell* map_abstractions[2] = { nullptr, nullptr };
    int dimensions;
    int hierarchy_size;
    int abstraction_size;
};


#endif //PATH_FINDING_MAP_ABSTRACTION_MASTER_H
