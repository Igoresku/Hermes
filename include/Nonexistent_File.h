//
// Created by Igor Duric on 4/19/19.
//

#ifndef PATH_FINDING_NONEXISTENT_FILE_H
#define PATH_FINDING_NONEXISTENT_FILE_H

#include <exception>
#include <string>

class Nonexistent_File: public std::exception {
public:
    explicit Nonexistent_File(std::string);

    const char* what() const noexcept override {
        return message;
    }

    ~Nonexistent_File() override { delete[] message; }
private:
    char* message;
};


#endif //PATH_FINDING_NONEXISTENT_FILE_H
