cmake_minimum_required(VERSION 2.8)
project(trajopt)

find_package(Eigen REQUIRED)
find_package(Boost COMPONENTS system python thread program_options REQUIRED)


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(BUILD_SHARED_LIBS off)

add_subdirectory(lib)
add_subdirectory(src)

