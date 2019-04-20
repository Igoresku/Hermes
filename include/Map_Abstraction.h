//
// Created by Igor Duric on 4/20/19.
//

#ifndef PATH_FINDING_MAP_ABSTRACTION_H
#define PATH_FINDING_MAP_ABSTRACTION_H

#include "Zone.h"

class Map_Abstraction: public Zone {
public:
    Map_Abstraction(int x, int y, int capacity);

    bool Find_Path(Cell**, int, Cell**, int) override;

private:

};


#endif //PATH_FINDING_MAP_ABSTRACTION_H
