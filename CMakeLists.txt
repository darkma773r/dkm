cmake_minimum_required(VERSION 2.8)
project(dkm C CXX)

set(dkm_VERSION_MAJOR 0)
set(dkm_VERSION_MINOR 1)

### Build ###

find_package(Threads REQUIRED)

include_directories(
    include
)

### Testing ###

enable_testing()
find_package(GTest REQUIRED)
include_directories(
    test
    ${GTEST_INCLUDE_DIRS}
)

add_executable(run_tests
    test/run_tests.cpp
    test/dkm/math/matrix_test.cpp
)
target_link_libraries(run_tests 
    ${GTEST_BOTH_LIBRARIES} 
    ${CMAKE_THREAD_LIBS_INIT}
)
add_test(Tests run_tests)



