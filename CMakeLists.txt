cmake_minimum_required(VERSION 3.10)

# set the project name
project(5806Project)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
include_directories(include)
file(GLOB SOURCES "src/*.cc")
# add the executable
add_executable(5806Project ${SOURCES})

