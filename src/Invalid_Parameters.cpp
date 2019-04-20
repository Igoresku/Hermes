//
// Created by Igor Duric on 4/20/19.
//

#include "../include/Invalid_Parameters.h"

Invalid_Parameters::Invalid_Parameters(int dimensions, int abstraction_size) {
    message = new char[120]; message[0] = '\0';
    strcat(message, "Invalid parameters (abstraction size: ");
    strcat(message, std::to_string(abstraction_size).c_str());
    strcat(message, " isn't a modulus of dimensions: ");
    strcat(message, std::to_string(dimensions).c_str());
    strcat(message, " ; Or one or both of them are negative)\n");
}

Invalid_Parameters::Invalid_Parameters(int max_agent_size) {
    message = new char[100]; message[0] = '\0';
    strcat(message, "Invalid parameter (max agent size: ");
    strcat(message, std::to_string(max_agent_size).c_str());
    strcat(message, " isn't in range [1,3])\n");
}