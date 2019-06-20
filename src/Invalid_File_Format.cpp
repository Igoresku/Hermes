//
// Created by Igor Duric on 4/19/19.
//

#include "../include/Invalid_File_Format.h"

Invalid_File_Format::Invalid_File_Format(int abstraction_size, int dimensions) {
    message = new char[110]; message[0] = '\0';
    strcat(message, "File is in invalid format (abstraction size: ");
    strcat(message, std::to_string(abstraction_size).c_str());
    strcat(message, " isn't a modulus of dimensions: ");
    strcat(message, std::to_string(dimensions).c_str());
    strcat(message, ")\n");
} /// Invalid_File_Format : END

Invalid_File_Format::Invalid_File_Format(char character) {
    message = new char[35]; message[0] = '\0';
    char* char_ptr = new char; *char_ptr = character;
    strcat(message, "File is in invalid format (unknown symbol: ");
    strcat(message, char_ptr);
    strcat(message, ")\n");
} /// Invalid_File_Format : END