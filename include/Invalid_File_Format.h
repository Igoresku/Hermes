//
// Created by Igor Duric on 4/19/19.
//

#ifndef PATH_FINDING_INVALID_FILE_FORMAT_H
#define PATH_FINDING_INVALID_FILE_FORMAT_H

#include <exception>
#include <string>

class Invalid_File_Format: public std::exception {
public:
    Invalid_File_Format(int, int);
    explicit Invalid_File_Format(char);

    const char* what() const noexcept override {
        return message;
    }

    ~Invalid_File_Format() override { delete[] message; }
private:
    char* message;
};


#endif //PATH_FINDING_INVALID_FILE_FORMAT_H
