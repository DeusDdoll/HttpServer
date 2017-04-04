cmake_minimum_required (VERSION 2.8)
project (HttpServer)
set (CMAKE_CXX_STANDERD 14)

set (CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package (GTest REQUIRED)

include_directories (${GTEST_INCLUDE_DIRS})
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/include/)

set (SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set (INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/http)
set (UNIT_TESTS ${CMAKE_CURRENT_SOURCE_DIR}/test)

file (GLOB_RECURSE SOURCE ${SOURCE_DIR}/*.cpp)
file (GLOB_RECURSE HEADERS ${INCLUDE_DIR}/*.hpp)
file (GLOB_RECURSE TESTS ${UNIT_TESTS}/*.cpp
                         ${UNIT_TESTS}/*.hpp)

add_library (${PROJECT_NAME} SHARED ${SOURCE} ${HEADERS})

target_link_libraries (${PROJECT_NAME} pthread)

install (TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION lib COMPONENT devel)

install (DIRECTORY ${INCLUDE_DIR}
    DESTINATION include)

enable_testing()

add_executable ("${PROJECT_NAME}_test" ${TESTS})
target_link_libraries ("${PROJECT_NAME}_test" ${PROJECT_NAME} ${GTEST_BOTH_LIBRARIES})

add_test ("${PROJECT_NAME}_test" "${PROJECT_NAME}_test")