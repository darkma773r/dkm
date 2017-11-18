cmake_minimum_required(VERSION 2.8)
project(dkm)

set(dkm_VERSION_MAJOR 0)
set(dkm_VERSION_MINOR 1)

### Build ###

find_package(Threads REQUIRED)

include_directories(
    ${dkm_SOURCE_DIR}/include
)

### Testing ###

enable_testing()
find_package(GTest REQUIRED)
include_directories(
    ${dkm_SOURCE_DIR}/test
    ${GTEST_INCLUDE_DIRS}
)

add_executable(math_tests
    ${dkm_SOURCE_DIR}/test/run_tests.cpp
    ${dkm_SOURCE_DIR}/test/dkm/math/matrix_util_test.cpp
    ${dkm_SOURCE_DIR}/test/dkm/math/matrix_test.cpp
    ${dkm_SOURCE_DIR}/test/dkm/math/vector_test.cpp
    ${dkm_SOURCE_DIR}/test/dkm/math/vector2_test.cpp
    ${dkm_SOURCE_DIR}/test/dkm/math/vector3_test.cpp
    ${dkm_SOURCE_DIR}/test/dkm/math/vector4_test.cpp
    ${dkm_SOURCE_DIR}/test/dkm/math/quaternion_util_test.cpp
    ${dkm_SOURCE_DIR}/test/dkm/math/quaternion_test.cpp
)
target_link_libraries(math_tests 
    ${GTEST_BOTH_LIBRARIES} 
    ${CMAKE_THREAD_LIBS_INIT}
)
add_test(MathTests math_tests)

### Installation ###
install(DIRECTORY ${dkm_SOURCE_DIR}/include/dkm
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include
)

