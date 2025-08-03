cmake_minimum_required(VERSION 3.28)
project(sauron)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}")

#setting compiler to mpicxx as we will do parallel
set(CMAKE_CXX_COMPILER ${mpicxx})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}")

find_package(Eigen3 REQUIRED)
find_package(MPI REQUIRED)
find_package(LibMesh REQUIRED)
find_package(GTest REQUIRED)

include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(${LIBMESH_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)


add_subdirectory(src)
add_subdirectory(test)


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()


target_link_libraries(sauron ray_tracing_sources ${LIBMESH_LINK_FLAGS})
add_executable(sauron_exe ${CMAKE_CURRENT_SOURCE_DIR}/src/SauronApp.C)


