cmake_minimum_required(VERSION 2.8)

project(TCP_HOLE_PUNCHING)

# enable c++14 support
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(WARNING_FLAGS "-Wall -Wextra ")
set(SHARED_FLAGS "${WARNING_FLAGS}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SHARED_FLAGS} -std=c++14 -pthread")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")


# Boost
find_package(Boost COMPONENTS program_options filesystem system context coroutine)
if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
endif()

# Local header files are placed in the include directory.
include_directories(inc)

# main module
add_subdirectory(src)
