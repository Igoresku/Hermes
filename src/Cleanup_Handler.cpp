//
// Created by Igor Duric on 11/23/19.
//

#include "../include/Cleanup_Handler.h"

Cleanup_Handler::Cleanup_Handler() = default;

void Cleanup_Handler::Stub(void* me) {
    auto cleanup_handler = (Cleanup_Handler*) me;
    cleanup_handler->Cleanup();
} /// Stub : END

Cleanup_Handler::~Cleanup_Handler() = default;