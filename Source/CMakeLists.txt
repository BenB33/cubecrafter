cmake_minimum_required(VERSION 3.20.0)

project(CubedCrafter)

# Set configuration types
set(CMAKE_CONFIGURATION_TYPES "Debug;Release")

# Set defines based on config types (Debug)
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CSS_FLAGS_DEBUG} -DCC_BUILD_DEBUG")

# Set defines based on config types (Release)
set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CSS_FLAGS_RELEASE} -DCC_BUILD_RELEASE -DNDEBUG")


# Add C++ Source files to project.
# Use source_group to create filters in visual studio
file(GLOB CORE_FILES CONFIGURE_DEPENDS "cubedcrafter/*cpp" "cubedcrafter/*.h")
source_group("CubedCrafter" FILES ${CORE_FILES})

file(GLOB GRAPHICS_FILES CONFIGURE_DEPENDS "cubedcrafter/graphics/*.cpp" "cubedcrafter/graphics/*.h")
source_group("CubedCrafter\\Graphics" FILES ${GRAPHICS_FILES})

file(GLOB ENTITY_FILES CONFIGURE_DEPENDS "cubedcrafter/entities/*.cpp" "cubedcrafter/entities/*.h")
source_group("CubedCrafter\\Entities" FILES ${ENTITY_FILES})

file(GLOB SHADER_SOURCE_FILES CONFIGURE_DEPENDS "../Resources/Shaders/*.glsl")
source_group("CubedCrafter\\Shaders" FILES ${SHADER_SOURCE_FILES})

# Set build target to an executable binary
add_executable(${PROJECT_NAME} ${CORE_FILES} ${GRAPHICS_FILES} ${ENTITY_FILES} ${SHADER_SOURCE_FILES})



# ***** Platform Checking ***** # 
# If on Windows, set defines and compiler flags
if(WIN32)
	add_definitions(-DCC_PLATFORM_WINDOWS)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /Ob2 /Oi /Ot /GT /GS- /Gy- /fp:fast /fp:except- /GR-")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od /Zi")
	set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
endif (WIN32)

# If on Apple, set defines and compiler flags
if (APPLE)
	add_definitions(-DCC_PLATFORM_MACOS)
endif (APPLE)

# If on Linux, set defines and compiler flags
if (${CMAKE_SYSTEM} MATCHES "Linux")
	add_definitions(-DCC_PLATFORM_LINUX)
endif (${CMAKE_SYSTEM} MATCHES "Linux")

# *****  End of Platform Checking ***** # 



#Set C++ Standard to C++ 17
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

# Set this project as the visual studio startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT CubedCrafter)

# GLFW Library
add_subdirectory(Dependencies/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

# Glad Library
add_subdirectory(Dependencies/glad)
target_link_libraries(${PROJECT_NAME} glad)

# glm Library
target_include_directories(${PROJECT_NAME} PRIVATE "Dependencies/glm")

# Include files from project as if the file was in the root directory
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/cubedcrafter")