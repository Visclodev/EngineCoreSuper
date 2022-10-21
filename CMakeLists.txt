cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

Project (EngineCoreSuper)
FILE(GLOB ENGINESRC src/*.cpp)
FILE(GLOB COMPONENTS src/Components/*.hpp)
FILE(GLOB SYSTEMSHEADERS src/Systems/*.hpp)
FILE(GLOB SYSTEMSCODE src/Systems/*.cpp)

link_libraries(sfml-graphics sfml-audio sfml-window sfml-system)

add_library(EngineCoreSuper SHARED
    ${ENGINESRC}
    ${COMPONENTS}
    ${SYSTEMSHEADERS}
    ${SYSTEMSCODE}
)
set_target_properties(EngineCoreSuper PROPERTIES PUBLIC_HEADER include/EngineCoreSuper.hpp)
