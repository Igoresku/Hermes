//
// Created by Igor Duric on 4/16/19.
//

#ifndef PATH_FINDING_LOGGER_H
#define PATH_FINDING_LOGGER_H

#include <iostream>

class Logger {
public:
    static Logger* Get_Logger_Instance();
private:
    static Logger* logger;
public:

protected:
    Logger() = default;
private:
    std::ostream* agent_log_target = &std::cout;
    std::ostream* game_map_log_target = &std::cout;

    std::string standard_agent_log_target = "agent_log.txt";
    std::string standard_map_log_target = "game_map_log.txt ";
    std::string agent_log_files = "";
    std::string game_map_log_files = "";
};


#endif //PATH_FINDING_LOGGER_H
