//
// Created by Igor Duric on 4/20/19.
//

#ifndef PATH_FINDING_INVALID_PARAMETERS_H
#define PATH_FINDING_INVALID_PARAMETERS_H

#include <exception>
#include <string>

class Invalid_Parameters: public std::exception {
public:
    Invalid_Parameters(int, int);
    explicit Invalid_Parameters(int);

    const char* what() const noexcept override {
        return message;
    }

    ~Invalid_Parameters() override { delete[] message; }
private:
    char* message;
};


#endif //PATH_FINDING_INVALID_PARAMETERS_H
