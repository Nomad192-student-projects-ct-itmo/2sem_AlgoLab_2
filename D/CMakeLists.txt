cmake_minimum_required(VERSION 3.20)

project(D)

set(CMAKE_CXX_STANDARD 14)

add_compile_definitions(TREE_TYPE=int) #unsigned\ int
add_compile_definitions(TREE_TYPE_SP="d")

add_library(AlmostTree STATIC test_system/AlmostTree.hpp test_system/AlmostTree.cpp)
add_library(TestTree STATIC test_system/TestTree.hpp test_system/TestTree.cpp)
add_library(D_Test STATIC test_system/AVL.hpp test_system/D_Test.hpp test_system/D_Test.cpp)

target_link_libraries(D_Test TestTree)
target_link_libraries(D_Test AlmostTree)

add_executable(${PROJECT_NAME} D.cpp)

target_link_libraries(${PROJECT_NAME} D_Test)