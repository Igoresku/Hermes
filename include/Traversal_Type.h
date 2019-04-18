//
// Created by Igor Duric on 4/16/19.
//

#ifndef PATH_FINDING_TRAVERSAL_TYPE_H
#define PATH_FINDING_TRAVERSAL_TYPE_H

#include <string>

enum class Traversal_Type : int {Walking = 0, Swimming = 1, Flying = 2};

std::string Print_Traversal_Type(const Traversal_Type&s);

#endif //PATH_FINDING_TRAVERSAL_TYPE_H
