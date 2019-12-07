//
// Created by Igor Duric on 11/23/19.
//

#ifndef PATH_FINDING_CLEANUP_HANDLER_H
#define PATH_FINDING_CLEANUP_HANDLER_H

/** Extending classes implement Cleanup method that is called
 * on thread cancellation or exit
 * -----------------------------------------------------------------
 * NOTE!!! This is used by following calls:
 * pthread_cleanup_push(Cleanup_Handler::Stub, cleanup_handler);
 * pthread_cleanup_pop(execute);
 * -> calls have to be paired and on the same indentation!
 * -----------------------------------------------------------------
 * cleanup_handler is a pointer to a Cleanup_Handler,
 * execute is an integer which denotes whether the handler
 * being popped is to be currently called (non-zero) or not (zero)
 * remember to destroy the object if it is on heap (not on stack) */
class Cleanup_Handler {
public: /// META
    static void Stub(void*);
public:
    Cleanup_Handler();

    virtual ~Cleanup_Handler() = 0;
private:
    virtual void Cleanup() = 0;
};


#endif //PATH_FINDING_LAST_WORDS_H
