cmake_minimum_required(VERSION 3.26)

project(HelloRaylib VERSION 0.0.1 LANGUAGES CXX)

include(cmake/get_cpm.cmake)
include(cmake/compiler_check.cmake)

CPMAddPackage("gh:raysan5/raylib#5.0")
CPMAddPackage("gh:raysan5/raygui#4.0")
include_directories(${raygui_SOURCE_DIR}/src)
#CPMAddPackage("gh:raysan5/rpng#1.0")

add_executable(HelloRaylib main.cpp "assets/Cell.h" "assets/Cell.cpp" "assets/Square.h" "assets/Square.cpp" "assets/Obstacle.h" "assets/Obstacle.cpp")
target_link_libraries(HelloRaylib PUBLIC raylib)