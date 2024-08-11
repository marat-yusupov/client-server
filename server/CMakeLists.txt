cmake_minimum_required(VERSION 3.8)

project(server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED COMPONENTS system)
find_package(RapidJSON)

set(SOURCES "*.cpp"
            "src/*.cpp"
            "src/network/*.cpp"
            "src/request/*.cpp"
            "src/request/models/*.cpp")

file(GLOB SOURCES ${SOURCES})

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
