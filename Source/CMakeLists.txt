cmake_minimum_required(VERSION 3.20.0)

project(CubedCrafter)

add_executable(${PROJECT_NAME} main.cpp)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT CubedCrafter)

# GLFW Library
add_subdirectory(Dependencies/glfw)
target_link_libraries(${PROJECT_NAME} glfw)