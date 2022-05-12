cmake_minimum_required(VERSION 3.20)

project(C)

set(CMAKE_CXX_STANDARD 14)

add_compile_definitions(TREE_TYPE=unsigned\ int)
add_compile_definitions(TREE_TYPE_SP="u")

add_library(AlmostTree STATIC AlmostTree.h AlmostTree.cpp)
add_library(TestTree STATIC TestTree.h TestTree.cpp)
add_library(C_Test STATIC C_Test.h C_Test.cpp)

target_link_libraries(C_Test TestTree)
target_link_libraries(C_Test AlmostTree)

add_executable(${PROJECT_NAME} C.cpp)

target_link_libraries(${PROJECT_NAME} C_Test)