file(GLOB SAURON_SOURCES *.C)

add_library(sauron SHARED ${SAURON_SOURCES})

target_include_directories(sauron
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
        ${EIGEN3_INCLUDE_DIR}
        ${LIBMESH_INCLUDE_DIRS}
        ${MPI_INCLUDE_PATH}
)

target_link_libraries(sauron
        PUBLIC
        ${LIBMESH_LIBRARIES}
        MPI::MPI_CXX
        OpenMP::OpenMP_CXX
)

# Separate executable target
add_executable(sauron_exe SauronApp.C)
target_link_libraries(sauron_exe sauron)