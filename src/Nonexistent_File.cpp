//
// Created by Igor Duric on 4/19/19.
//

#include "../include/Nonexistent_File.h"

Nonexistent_File::Nonexistent_File(std::string file_name) {
    char message[35]; message[0] = '\0';
    message[0] = '\0';
    strcat(message, "File ");
    strcat(message, file_name.c_str());
    strcat(message, " does not exist\n");
}