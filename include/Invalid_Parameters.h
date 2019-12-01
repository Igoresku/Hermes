//
// Created by Igor Duric on 4/20/19.
//

#ifndef PATH_FINDING_INVALID_PARAMETERS_H
#define PATH_FINDING_INVALID_PARAMETERS_H

#include <exception>
#include <string>

/** Thrown by Map_Creator::Create_Map when its arguments are invalid. */
class Invalid_Parameters: public std::exception {
public:
    explicit Invalid_Parameters(int);
    explicit Invalid_Parameters(double);

    const char* what() const noexcept override {
        return message;
    }

    ~Invalid_Parameters() override;
private:
    char* message;
};


#endif //PATH_FINDING_INVALID_PARAMETERS_H
