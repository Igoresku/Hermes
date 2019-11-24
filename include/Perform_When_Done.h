//
// Created by Igor Duric on 11/23/19.
//

#ifndef PATH_FINDING_LAST_WORDS_H
#define PATH_FINDING_LAST_WORDS_H

/** Classes that extend this class implement a method that
 * thread is meant to perform when it it is finished */
class Perform_When_Done {
public:
    Perform_When_Done() = default;

    virtual void Perform_Action() = 0;

    // This should be = 0 (abstract), but wouldn't be compiled as such
    virtual ~Perform_When_Done();
};


#endif //PATH_FINDING_LAST_WORDS_H
