cmake_minimum_required(VERSION 3.28)

project(PangolinGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_executable(pango src/main.cpp)

target_link_libraries(pango PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/fonts
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

