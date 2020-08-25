cmake_minimum_required(VERSION 3.10)
project(joi_grad_shopping_cart_cpp)

set(CMAKE_CXX_STANDARD 11)
aux_source_directory(src EXE_SOURCES)
list(FILTER EXE_SOURCES INCLUDE REGEX "^.*.cc$")
add_executable(${PROJECT_NAME} ${EXE_SOURCES})

aux_source_directory(test TEST_SOURCES)
list(FILTER TEST_SOURCES INCLUDE REGEX "^.*_test.cc$")

if (NOT "${TEST_SOURCES}" STREQUAL "")
    list(FILTER EXE_SOURCES EXCLUDE REGEX "main.cc")
    add_executable(${PROJECT_NAME}_test ${EXE_SOURCES} ${TEST_SOURCES} test/test_main.cc)
    find_package(GTest REQUIRED)
    target_link_libraries(${PROJECT_NAME}_test GTest::GTest)
endif ()
