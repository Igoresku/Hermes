//
// Created by Igor Duric on 4/16/19.
//

#ifndef PATH_FINDING_TERRAIN_H
#define PATH_FINDING_TERRAIN_H

enum class Basic_Terrain_Type : unsigned char { LAND = 0x01, WATER = 0x02, IMPASSABLE = 0x03 };

typedef unsigned char Terrain;

Terrain Create_Terrain(Basic_Terrain_Type, Basic_Terrain_Type);
unsigned char Pack_Terrain(Terrain, Terrain);


#endif //PATH_FINDING_TRAVERSAL_TYPE_H
