
cmake_minimum_required(VERSION 3.17)

# set the project name.
project(NetTutorial VERSION 1.0)

set(CMAKE_DEBUG_POSTFIX debug)

# control where the static and shared libraries are built so that on windows
# we don't need to tinker with the path to run the executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# configure a header file to pass some of the CMake settings
# to the source code.
configure_file(config.h.in config.h)

add_subdirectory(common)
add_subdirectory(chapter_1)
