//
// Created by Igor Duric on 4/16/19.
//

#include "../include/Logger.h"

Logger* Logger::logger = nullptr;

Logger* Logger::Get_Logger_Instance() {
    if (logger == nullptr)
        logger = new Logger();

    return logger;
} /// Logger : END