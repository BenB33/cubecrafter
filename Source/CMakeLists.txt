cmake_minimum_required(VERSION 3.20.0)

project(CubedCrafter)

file(GLOB CORE_FILES CONFIGURE_DEPENDS "cubedcrafter/*cpp" "cubedcrafter/*.h")
source_group("CubedCrafter" FILES ${CORE_FILES})

file(GLOB GRAPHICS_FILES CONFIGURE_DEPENDS "cubedcrafter/graphics/*.cpp" "cubedcrafter/graphics/*.h")
source_group("CubedCrafter\\Graphics" FILES ${GRAPHICS_FILES})

add_executable(${PROJECT_NAME} ${CORE_FILES} ${GRAPHICS_FILES})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT CubedCrafter)

# GLFW Library
add_subdirectory(Dependencies/glfw)
target_link_libraries(${PROJECT_NAME} glfw)