cmake_minimum_required(VERSION 3.28)
project(libmesh_track_length)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}")

#setting compiler to mpicxx as we will do parallel
set(CMAKE_CXX_COMPILER ${mpicxx})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}")
find_package(Eigen3 REQUIRED)
find_package(MPI REQUIRED)
find_package(LibMesh REQUIRED)

include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(${LIBMESH_INCLUDE_DIRS})


add_subdirectory(src)
add_subdirectory(test)

add_executable(libmesh_track_length  ${CMAKE_CURRENT_SOURCE_DIR}/src/SauronApp.C)

target_link_libraries(libmesh_track_length ray_tracing_sources ${LIBMESH_LINK_FLAGS})