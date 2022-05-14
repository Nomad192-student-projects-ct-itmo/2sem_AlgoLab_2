cmake_minimum_required(VERSION 3.20)

project(C)

set(CMAKE_CXX_STANDARD 14)

add_compile_definitions(TREE_TYPE=int) #unsigned\ int
add_compile_definitions(TREE_TYPE_SP="d")

add_library(AlmostTree STATIC AlmostTree.hpp AlmostTree.cpp)
add_library(TestTree STATIC TestTree.hpp TestTree.cpp)
add_library(C_Test STATIC AVL.hpp C_Test.hpp C_Test.cpp)

target_link_libraries(C_Test TestTree)
target_link_libraries(C_Test AlmostTree)

add_executable(${PROJECT_NAME} C.cpp)

target_link_libraries(${PROJECT_NAME} C_Test)