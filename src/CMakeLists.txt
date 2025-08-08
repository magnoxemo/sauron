file(GLOB SAURON_SOURCES *.C)

add_library(sauron_lib SHARED ${SAURON_SOURCES})

#adding libmesh openmp and mpi
target_link_libraries(sauron_lib
        ${LIBMESH_LINK_FLAGS}
        MPI::MPI_CXX
        OpenMP::OpenMP_CXX
)