
cmake_minimum_required(VERSION 3.10)

# set the project name.
project(NetTutorial VERSION 1.0)

set(CMAKE_DEBUG_POSTFIX debug)

# control where the static and shared libraries are built so that on windows
# we don't need to tinker with the path to run the executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

include(CheckIncludeFile)
include(CheckFunctionExists) 
check_include_file(sys/select.h  HAVE_SYS_SELECT_H)
check_include_file(poll.h HAVE_POLL_H)
check_include_file(strings.h HAVE_STRINGS_H)
check_include_file(sys/ioctl.h HAVE_SYS_IOCTL_H)
check_include_file(sys/filio.h HAVE_SYS_FILIO_H)
check_include_file(sys/sockio.h HAVE_SYS_SOCKIO_H)
check_include_file(pthread.h HAVE_PTHREAD_H)

check_function_exists(bzero HAVE_BZERO)
check_function_exists(gethostbyname2 HAVE_GETHOSTBYNAME2)


# configure a header file to pass some of the CMake settings
# to the source code.
configure_file(config.h.in config.h)

add_subdirectory(common)
add_subdirectory(chapter_1)
