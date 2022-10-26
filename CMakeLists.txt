cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

Project (EngineCoreSuper)
FILE(GLOB ENGINESRC src/*.cpp)
FILE(GLOB PARTICLE_EMITTER src/Components/ParticleEmitter.cpp)
FILE(GLOB SYSTEMSCODE src/Systems/*.cpp)

link_libraries(sfml-graphics sfml-audio sfml-window sfml-system)

add_library(EngineCoreSuper SHARED
    ${ENGINESRC}
    ${PARTICLE_EMITTER}
    ${SYSTEMSCODE}
)

set_target_properties(EngineCoreSuper PROPERTIES 
    PUBLIC_HEADER include/EngineCoreSuper/EngineCoreSuper.hpp)
