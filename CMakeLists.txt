cmake_minimum_required(VERSION 3.10)
project(Projet)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets CONFIG REQUIRED)

file (GLOB_RECURSE sourceCode src/*.cpp src/*.h)

add_executable(Projet ${sourceCode})

target_link_libraries(Projet Qt5::Widgets)