cmake_minimum_required(VERSION 3.20)

project(F)

set(CMAKE_CXX_STANDARD 14)

add_compile_definitions(TREE_TYPE=unsigned\ int)
add_compile_definitions(TREE_TYPE_SP="u")
add_compile_definitions(TREE_TYPE_SUM=unsigned\ long\ long\ int)
add_compile_definitions(TREE_TYPE_SUM_SP="llu")

add_library(AlmostTree STATIC test_system/AlmostTree.hpp test_system/AlmostTree.cpp)
add_library(TestTree STATIC test_system/TestTree.hpp test_system/TestTree.cpp)
add_library(F_Test STATIC test_system/AVL.hpp test_system/F_Test.hpp test_system/F_Test.cpp)

target_link_libraries(F_Test TestTree)
target_link_libraries(F_Test AlmostTree)

add_executable(${PROJECT_NAME} F.cpp)

target_link_libraries(${PROJECT_NAME} F_Test)