cmake_minimum_required(VERSION 3.10)
project(ClNotes)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(SOURCE_FILES
    src/main.cpp
    src/cli.cpp
    src/database.cpp
)

include_directories(include)

add_executable(ClNotes ${SOURCE_FILES})

find_package(SQLite3 REQUIRED)
target_link_libraries(ClNotes PRIVATE SQLite::SQLite3)