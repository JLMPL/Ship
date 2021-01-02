cmake_minimum_required(VERSION 3.5.0)
project(ASS)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(PROJECT_LINK_LIBS -lm -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system -lbox2d -llua5.3 -lSDL2 -lSDL2main)

link_directories(/usr/local/lib)
link_directories(./)

# -fno-exceptions
add_definitions(-g -std=c++17 -Wall -Wfatal-errors -Wall)

include_directories(src)
include_directories(src/Libs)

file(GLOB src0 "src/*.cpp")
file(GLOB src1 "src/*/*.cpp")
file(GLOB src2 "src/*/*/*.cpp")
file(GLOB src3 "src/*/*/*/*.cpp")

add_executable(out
    ${src0}
    ${src1}
    ${src2}
    ${src3}
)
target_link_libraries(out ${PROJECT_LINK_LIBS})
