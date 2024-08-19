#pragma once

#include <iostream>

namespace generic {

inline void Log(const char* func_name, std::string const& message) {
    std::cout << "[SERVER::" << func_name << "] " + message << std::endl;
}

inline void LogWarn(const char* func_name, std::string const& message) {
    std::cout << "[SERVER::WARNING::" << func_name << "] " + message << std::endl;
}

inline void LogErr(const char* func_name, std::string const& message) {
    std::cout << "[SERVER::ERROR::" << func_name << "] " + message << std::endl;
}

}  // namespace generic
