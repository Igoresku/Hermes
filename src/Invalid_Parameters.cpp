//
// Created by Igor Duric on 4/20/19.
//

#include "../include/Invalid_Parameters.h"

Invalid_Parameters::Invalid_Parameters(int dimensions) {
    message = new char[120]; message[0] = '\0';
    strcat(message, "Invalid parameter dimensions = ");
    strcat(message, std::to_string(dimensions).c_str());
    strcat(message, "; It isn't a power of [16, 12, 8, 4] or it's negative\n");
} /// Invalid_Parameters : END

Invalid_Parameters::Invalid_Parameters(double factor) {
    message = new char[100]; message[0] = '\0';
    strcat(message, "Invalid parameter factor: ");
    strcat(message, std::to_string(factor).c_str());
    strcat(message, " isn't in range [0.0, 100.0])\n");
} /// Invalid_Parameters : END

Invalid_Parameters::~Invalid_Parameters() {
    delete[] message;
} /// ~Invalid_Parameters : END