cmake_minimum_required(VERSION 3.20)

project(F)

set(CMAKE_CXX_STANDARD 14)

add_compile_definitions(TREE_TYPE=unsigned\ int)
add_compile_definitions(TREE_TYPE_SP="u")

add_library(AlmostTree STATIC AlmostTree.hpp AlmostTree.cpp)
add_library(F_Test STATIC AVL.hpp F_Test.hpp F_Test.cpp)

target_link_libraries(F_Test AlmostTree)

add_executable(${PROJECT_NAME} F.cpp)

target_link_libraries(${PROJECT_NAME} F_Test)