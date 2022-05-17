cmake_minimum_required(VERSION 3.20)

project(F)

set(CMAKE_CXX_STANDARD 14)

add_compile_definitions(TREE_TYPE=int) #unsigned\ int
add_compile_definitions(TREE_TYPE_SP="d")

add_executable(${PROJECT_NAME} F.cpp)