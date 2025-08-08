file(GLOB TEST_SOURCES *.C)

#adding test executables for every case
foreach(TEST_SOURCE ${TEST_SOURCES})
        get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
        add_executable(${TEST_NAME} ${TEST_SOURCE})
        target_link_libraries(${TEST_NAME}
                sauron_lib
                ${LIBMESH_LINK_FLAGS}
                MPI::MPI_CXX
                OpenMP::OpenMP_CXX
                GTest::GTest
                GTest::Main
        )
endforeach()