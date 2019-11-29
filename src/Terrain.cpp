//
// Created by Igor Duric on 4/16/19.
//

#include "../include/Terrain.h"

Terrain Create_Terrain(Basic_Terrain_Type first, Basic_Terrain_Type second) {
    Terrain terrain;

    // I want the combinations to be: [LAND/LAND], [WATER/WATER], [LAND/WATER],
    // [LAND/IMPASSABLE], [WATER/IMPASSABLE], [IMPASSABLE/IMPASSABLE]
    if ((first == Basic_Terrain_Type::IMPASSABLE) || (second == Basic_Terrain_Type::IMPASSABLE)) {
        if (first == Basic_Terrain_Type::IMPASSABLE)
            terrain = ((unsigned char) second << 2) | (unsigned char) first;
        else
            terrain = ((unsigned char) first << 2) | (unsigned char) second;

        return terrain;
    } else if (first == Basic_Terrain_Type::WATER)
        terrain = ((unsigned char) second << 2) | (unsigned char) first;
    else
        terrain = ((unsigned char) first << 2) | (unsigned char) second;

    return terrain;
} /// Create_Terrain : END

unsigned char Pack_Terrain(Terrain first, Terrain second) {
    return ((unsigned char) first << 4) | (unsigned char) second;
} /// Pack_Terrain : END