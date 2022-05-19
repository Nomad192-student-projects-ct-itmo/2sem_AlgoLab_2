cmake_minimum_required(VERSION 3.20)

project(D)

set(CMAKE_CXX_STANDARD 14)

add_compile_definitions(TREE_TYPE=int) #unsigned\ int
add_compile_definitions(TREE_TYPE_SP="d")

add_library(AlmostTree STATIC AlmostTree.hpp AlmostTree.cpp)
add_library(TestTree STATIC TestTree.hpp TestTree.cpp)
add_library(D_Test STATIC AVL.hpp D_Test.hpp D_Test.cpp)

target_link_libraries(D_Test TestTree)
target_link_libraries(D_Test AlmostTree)

add_executable(${PROJECT_NAME} D.cpp)

target_link_libraries(${PROJECT_NAME} D_Test)