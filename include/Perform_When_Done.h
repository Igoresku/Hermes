//
// Created by Igor Duric on 11/23/19.
//

#ifndef PATH_FINDING_LAST_WORDS_H
#define PATH_FINDING_LAST_WORDS_H

/** Classes that extend this class implement a method that
 * thread is meant to call when it it is finished */
class Perform_When_Done {
public:
    Perform_When_Done();

    virtual void Perform_Action() = 0;

    virtual ~Perform_When_Done() = 0;
};


#endif //PATH_FINDING_LAST_WORDS_H
