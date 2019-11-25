//
// Created by Igor Duric on 4/20/19.
//

#ifndef PATH_FINDING_MAP_ABSTRACTION_H
#define PATH_FINDING_MAP_ABSTRACTION_H

#include "Zone.h"

class Map_Abstraction_Level : public Zone {
public:
    Map_Abstraction_Level(int x, int y, int level, int capacity) : Zone(x, y, level, capacity) {};

    bool Find_Path(Cell**, int, Cell**, int) override;

    ~Map_Abstraction_Level() override;
};


#endif //PATH_FINDING_MAP_ABSTRACTION_H
