cmake_minimum_required(VERSION 3.26)
project(sauron)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}")


find_package(Eigen3 REQUIRED)
find_package(MPI REQUIRED)
find_package(LibMesh REQUIRED)
find_package(OpenMP REQUIRED)
find_package(GTest REQUIRED)

include_directories(
        ${EIGEN3_INCLUDE_DIR}
        ${LIBMESH_INCLUDE_DIRS}
        ${MPI_CXX_INCLUDE_PATH}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(src)
add_subdirectory(test)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()