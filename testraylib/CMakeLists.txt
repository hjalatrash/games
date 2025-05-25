cmake_minimum_required(VERSION 3.11)
# Set minimum policy version to handle raylib's CMake requirements
cmake_policy(VERSION 3.5...3.27)

project(testraylib C)

# Set raylib source path
set(RAYLIB_PATH "C:/raylib/raylib")
set(RAYLIB_SRC "${RAYLIB_PATH}/src")

# Platform specific definitions
add_definitions(-DPLATFORM_DESKTOP)
add_definitions(-DGRAPHICS_API_OPENGL_33)

# Include GLFW source files
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory("${RAYLIB_SRC}/external/glfw" glfw_build)

# Raylib source files
set(RAYLIB_SOURCES
    "${RAYLIB_SRC}/rcore.c"
    "${RAYLIB_SRC}/rshapes.c"
    "${RAYLIB_SRC}/rtextures.c"
    "${RAYLIB_SRC}/rtext.c"
    "${RAYLIB_SRC}/utils.c"
    "${RAYLIB_SRC}/rmodels.c"
)

# Create raylib library
add_library(raylib STATIC ${RAYLIB_SOURCES})
target_include_directories(raylib 
    PUBLIC ${RAYLIB_SRC}
    PUBLIC "${RAYLIB_SRC}/external/glfw/include"
)

# Add required Windows libraries for raylib
target_link_libraries(raylib PRIVATE glfw winmm gdi32 opengl32)

# Create our executable
add_executable(${PROJECT_NAME} main.c)

# Link with raylib
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Set C standard
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD_REQUIRED ON) 