cmake_minimum_required(VERSION 3.26)
project(MyTestProject)

find_package(GTest REQUIRED)
add_executable(my_test Test.C)

target_link_libraries(my_test
        PRIVATE MPI::MPI_CXX
        sauron

        GTest::GTest
        GTest::Main
        )