cmake_minimum_required(VERSION 3.28)
project(MyTestProject)

find_package(GTest REQUIRED)
add_executable(my_test Test.C)
target_link_libraries(my_test
        sauron
        GTest::GTest
        GTest::Main)