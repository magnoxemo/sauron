cmake_minimum_required(VERSION 3.28)
project(libmesh_track_length)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(src)
add_subdirectory(test)
add_executable(libmesh_track_length ${CMAKE_CURRENT_SOURCE_DIR}/src/main.C)
target_link_libraries(libmesh_track_length ray_tracing_sources)