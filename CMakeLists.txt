cmake_minimum_required(VERSION 3.8)
project(tilemap)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
set(SFML_DIR "/usr/include/SFML")

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

file(GLOB tilemap
        "include/*.h" "src/*.cpp")

add_executable(tilemap main.cpp ${tilemap})

target_link_libraries(tilemap sfml-graphics)
