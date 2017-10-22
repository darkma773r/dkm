cmake_minimum_required(VERSION 2.8)
project(dkm)

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

add_executable(math_tests
    test/run_tests.cpp
    test/dkm/math/matrix_util_test.cpp
    test/dkm/math/matrix_test.cpp
    test/dkm/math/vector_test.cpp
    test/dkm/math/vector2_test.cpp
    test/dkm/math/vector3_test.cpp
    test/dkm/math/vector4_test.cpp
    test/dkm/math/quaternion_util_test.cpp
    test/dkm/math/quaternion_test.cpp
)
target_link_libraries(math_tests 
    ${GTEST_BOTH_LIBRARIES} 
    ${CMAKE_THREAD_LIBS_INIT}
)
add_test(MathTests math_tests)



