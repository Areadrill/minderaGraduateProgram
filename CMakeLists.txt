cmake_minimum_required(VERSION 3.10)
project(AdjacentCellsChallenge)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

enable_testing()

find_package(PkgConfig REQUIRED)
pkg_check_modules(OpenCV REQUIRED opencv)

link_libraries(${OpenCV_LIBRARIES})

include_directories(include)
include_directories(${OpenCV_INCLUDE_DIRS})

add_subdirectory(src)