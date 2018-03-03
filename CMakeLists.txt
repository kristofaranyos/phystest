cmake_minimum_required(VERSION 3.9)
project(phystest)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
add_executable(phystest main.cpp)
target_link_libraries(phystest ${SDL2_LIBRARIES})