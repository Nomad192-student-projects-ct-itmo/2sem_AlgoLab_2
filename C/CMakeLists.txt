cmake_minimum_required(VERSION 3.20)

project(C)

set(CMAKE_CXX_STANDARD 14)

add_compile_definitions(TREE_TYPE=unsigned\ int)
add_compile_definitions(TREE_TYPE_SP="u")

add_library(AlmostTree STATIC AlmostTree.cpp AlmostTree.h)
add_library(TestTree STATIC TestTree.cpp TestTree.h)
add_library(C_Test STATIC C_Test.cpp C_Test.h)

target_link_libraries(C_Test AlmostTree)
target_link_libraries(C_Test TestTree)

add_executable(${PROJECT_NAME} C.cpp)

target_link_libraries(${PROJECT_NAME} C_Test)