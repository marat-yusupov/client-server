#pragma once

#include <iostream>
#include <thread>

namespace generic {

inline void Log(std::string const& message) {
    std::cout << "[SERVER::" << std::this_thread::get_id() << "]: " + message << std::endl;
}

inline void Log(const char* func_name, std::string const& message) {
    std::cout << "[SERVER::" << func_name << "::" << std::this_thread::get_id() << "]: " + message << std::endl;
}

inline void LogWarn(const char* func_name, std::string const& message) {
    std::cout << "[SERVER::WARNING::" << func_name << "::" << std::this_thread::get_id() << "]: " + message
              << std::endl;
}

inline void LogErr(const char* func_name, std::string const& message) {
    std::cout << "[SERVER::ERROR::" << func_name << "::" << std::this_thread::get_id() << "]: " + message << std::endl;
}

}  // namespace generic
