cmake_minimum_required(VERSION 3.5)
project(phystest)

set(CMAKE_CXX_STANDARD 11)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
add_executable(phystest main.cpp entity/AABB.cpp entity/AABB.hpp Constants.hpp SDLGraphicsWrapper.cpp SDLGraphicsWrapper.hpp PhysicsEngine.cpp PhysicsEngine.hpp module/PhysicsModule.hpp module/PhysicsModule.cpp module/PhysicsModule.hpp entity/PhysicsEntity.cpp entity/PhysicsEntity.hpp module/MoveModule.cpp module/MoveModule.hpp PhysicsIncludes.hpp)
target_link_libraries(phystest ${SDL2_LIBRARIES})