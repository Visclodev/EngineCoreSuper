cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

Project (testEngine)
FILE(GLOB SRC main.cpp)

link_libraries(
    EngineCoreSuper
    sfml-graphics
    sfml-audio
    sfml-window
    sfml-system
)

add_executable(testEngine ${SRC})
