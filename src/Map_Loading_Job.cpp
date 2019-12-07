//
// Created by Igor Duric on 12/4/19.
//

#include "../include/Map_Loading_Job.h"

Map_Loading_Job::Map_Loading_Job(std::string& map_name) : map_name(map_name) {}

void Map_Loading_Job::Do_Job() {
    std::ifstream input_File;
    input_File.open(map_name);
    if (!input_File)
        throw Nonexistent_File(map_name);

    input_File >> dimensions;

    raw_map = new char*[dimensions];
    for (int i = 0; i < dimensions; i++)
        raw_map[i] = new char[dimensions];

} /// Do_Job : END

Map_Loading_Job::~Map_Loading_Job() = default;