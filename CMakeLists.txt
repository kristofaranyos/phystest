cmake_minimum_required(VERSION 3.5)
project(phystest)

set(CMAKE_CXX_STANDARD 11)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
add_executable(phystest main.cpp AABB.cpp AABB.hpp Constants.hpp SDLWrapper.cpp SDLWrapper.hpp)
target_link_libraries(phystest ${SDL2_LIBRARIES})