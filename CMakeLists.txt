cmake_minimum_required(VERSION 3.26)
project(sauron)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}")

find_package(Eigen3 REQUIRED)
find_package(MPI REQUIRED) #for libmesh
find_package(LibMesh REQUIRED)
find_package(OpenMP REQUIRED) #needed for the parallel solve
find_package(GTest REQUIRED) #testing


include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(${LIBMESH_INCLUDE_DIRS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB SAURON_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()



add_subdirectory(src)
add_subdirectory(test)


add_executable(sauron_exe SauronApp.C)
target_link_libraries(sauron_exe sauron_lib)