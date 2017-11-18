cmake_minimum_required(VERSION 2.8)
project(dkm)

set(dkm_VERSION_MAJOR 0)
set(dkm_VERSION_MINOR 1)

set(INCLUDE_DIR ${dkm_SOURCE_DIR}/include)
set(SRC_DIR ${dkm_SOURCE_DIR}/src)
set(TEST_DIR ${dkm_SOURCE_DIR}/test)

### Build ###

# enable c++11
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

find_package(Threads REQUIRED)

include_directories(
    ${INCLUDE_DIR}
)

add_library(dkm 
    ${dkm_SOURCE_DIR}/src/dkm/util/log/logging.cpp
)

### Testing ###

enable_testing()
find_package(GTest REQUIRED)
include_directories(
    ${TEST_DIR}
    ${GTEST_INCLUDE_DIRS}
)

add_executable(math_tests
    ${TEST_DIR}/run_tests.cpp
    ${TEST_DIR}/dkm/math/matrix_util_test.cpp
    ${TEST_DIR}/dkm/math/matrix_test.cpp
    ${TEST_DIR}/dkm/math/vector_test.cpp
    ${TEST_DIR}/dkm/math/vector2_test.cpp
    ${TEST_DIR}/dkm/math/vector3_test.cpp
    ${TEST_DIR}/dkm/math/vector4_test.cpp
    ${TEST_DIR}/dkm/math/quaternion_util_test.cpp
    ${TEST_DIR}/dkm/math/quaternion_test.cpp
)
target_link_libraries(math_tests 
    ${GTEST_BOTH_LIBRARIES} 
    ${CMAKE_THREAD_LIBS_INIT}
)
add_test(MathTests math_tests)

### Installation ###
install(TARGETS dkm
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static
)
install(DIRECTORY ${INCLUDE_DIR}/dkm
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include
)

