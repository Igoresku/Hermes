//
// Created by Igor Duric on 12/4/19.
//

#ifndef PATH_FINDING_MAP_LOADING_JOB_H
#define PATH_FINDING_MAP_LOADING_JOB_H

#include <string>
#include "Job.h"
#include <fstream>
#include "Nonexistent_File.h"

class Map_Loading_Job : public Job {
public:
    explicit Map_Loading_Job(std::string&);

    void Do_Job() override;

    ~Map_Loading_Job() override;
private:
    const std::string map_name;
    char** raw_map;
    int dimensions;
};


#endif //PATH_FINDING_MAP_LOADING_JOB_H
