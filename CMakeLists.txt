cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

Project (EngineCoreSuper)
FILE(GLOB_RECURSE ENGINESRC src/*.cpp)

add_library(EngineCoreSuper SHARED ${ENGINESRC})
set_target_properties(EngineCoreSuper PROPERTIES PUBLIC_HEADER include/EngineCoreSuper.hpp)
