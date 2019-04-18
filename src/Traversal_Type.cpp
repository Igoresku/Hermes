//
// Created by Igor Duric on 4/16/19.
//

#include "../include/Traversal_Type.h"

std::string Print_Traversal_Type(const Traversal_Type& traversal_type) {
    static std::string strings[3] = { "Walking", "Swimming", "Flying" };

    return strings[(int)traversal_type];
}