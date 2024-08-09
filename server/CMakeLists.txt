cmake_minimum_required(VERSION 3.8)

project(gaijin_server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE main.cpp)
add_executable(main ${SOURCE})